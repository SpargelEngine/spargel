#include <metal_stdlib>
using namespace metal;

struct QuadData {
    float2 origin;
    float2 size;
    float2 cell_origin;
};

struct VertexData {
    float2 position [[attribute(0)]];
};

struct RasterData {
    float4 position [[position]];
    float2 texture_coord;
};

struct UniformData {
    float2 viewport;
};

[[vertex]] RasterData vertex_shader(uint vertex_id [[vertex_id]],
                                    uint instance_id [[instance_id]],
                                    VertexData in [[stage_in]],
                                    constant QuadData* quads [[buffer(1)]],
                                    constant UniformData& uniform [[buffer(2)]]) {
    float2 pixel_position = in.position * quads[instance_id].size + quads[instance_id].origin;

    RasterData out;
    out.position = float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixel_position / (uniform.viewport / 2.0);
    out.texture_coord = float2(in.position.x, 1.0 - in.position.y) * quads[instance_id].size + quads[instance_id].cell_origin;
    out.texture_coord /= float2(512, 512);
    return out;
}

[[fragment]] float4 fragment_shader(RasterData in [[stage_in]],
                                    texture2d<float> color_texture [[texture(0)]]) {
    constexpr sampler texture_sampler(mag_filter::linear, min_filter::linear);
    float4 color = float4(1.0, 0.0, 0.0, 1.0);
    color.a *= color_texture.sample(texture_sampler, in.texture_coord).a;
    return color;
}

[[kernel]] void add_arrays_old(constant float const* inA [[buffer(0)]],
                           constant float const* inB [[buffer(1)]],
                           device float* result [[buffer(2)]],
                           uint index [[thread_position_in_grid]]) {
    result[index] = inA[index] + inB[index];
}

struct SumArgs {
    constant uint& count [[id(0)]];
    constant float const* in1 [[id(1)]];
    constant float const* in2 [[id(2)]];
    device float* result [[id(3)]];
};

[[kernel]] void add_arrays(uint index [[thread_position_in_grid]],
                           device SumArgs& args [[buffer(0)]]) {
    if (index < args.count) {
        args.result[index] = args.in1[index] + args.in2[index];
    }
}

struct TileVertexData {
    float2 position [[attribute(0)]];
    float4 color [[attribute(1)]];
};

struct TileRasterData {
    float4 position [[position]];
    float4 color;
};

[[vertex]] TileRasterData tiles_vertex(uint vertex_id [[vertex_id]],
                                       TileVertexData in [[stage_in]],
                                       constant UniformData& uniform [[buffer(2)]]) {
    float2 pixel_position = in.position;

    TileRasterData out;
    out.position = float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixel_position / (uniform.viewport / 2.0);
    out.color = in.color;
    return out;
}

struct TileControl {
    uint batch;
};

struct TileFragData {
    atomic<uint> count;
};

[[fragment]] float4 tiles_fragment(TileRasterData in [[stage_in]],
                                   constant TileControl& control [[buffer(0)]],
                                   device TileFragData& data [[buffer(1)]]) {
    uint count = atomic_fetch_add_explicit(&data.count, 1, memory_order_relaxed);
    if (count > control.batch) {
        return float4(0.0, 0.0, 0.0, 1.0);
    }
    return in.color;
}

// ------------------ //
// Bitonic Merge Sort //
// ------------------ //

#define N 16 // let's sort 16 elements

struct SortData {
    device uint* data [[id(0)]];
};

void compareAndSwap(threadgroup uint* data, uint i, uint j) {
    if (data[i] > data[j]) {
        uint tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}

// group size should be (8, 1, 1)
[[kernel]] void bitonic_sort(uint id [[thread_index_in_threadgroup]],
                             device SortData& data [[buffer(0)]]) {
    threadgroup uint local[N];

    // Step 1. Read data. Each thread reads two value.
    local[id * 2] = data.data[id * 2];
    local[id * 2 + 1] = data.data[id * 2 + 1];

    // Step 2. Sort!
    for (uint h1 = 2; h1 <= N; h1 *= 2) {
        threadgroup_barrier(mem_flags::mem_none);

        uint d1 = ((id * 2) / h1) * h1;
        compareAndSwap(local, d1 + (id % (h1 / 2)), d1 + (h1 - 1 - (id % (h1 / 2))));

        for (uint h2 = h1 / 2; h2 > 1; h2 /= 2) {
            threadgroup_barrier(mem_flags::mem_none);

            uint d2 = ((id * 2) / h2) * h2;
            compareAndSwap(local, d2 + (id % (h2 / 2)), d2 + (id % (h2 / 2)) + (h2 / 2));
        }
    }

    //  Step 3. Write back.
    threadgroup_barrier(mem_flags::mem_none);

    data.data[id * 2] = local[id * 2];
    data.data[id * 2 + 1] = local[id * 2 + 1];
}
