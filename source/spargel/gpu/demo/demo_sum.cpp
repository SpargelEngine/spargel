#include <spargel/base/command_line.h>
#include <spargel/gpu/gpu.h>
#include <spargel/resource/directory.h>

//
#include <stdio.h>

using namespace spargel;

static constexpr u32 count = 3;
static constexpr float arr1[] = {1.0, 2.0, 3.0};
static constexpr float arr2[] = {4.0, 5.0, 6.0};

int main(int argc, char* argv[]) {
    base::CommandLine cmdline(argc, argv);

    auto resource_manager = resource::makeRelativeManager(base::string("resources"));
    gpu::DeviceKind backend = gpu::DeviceKind::unknown;
    if (cmdline.hasSwitch("metal")) {
        backend = gpu::DeviceKind::metal;
    }
    if (cmdline.hasSwitch("vulkan")) {
        backend = gpu::DeviceKind::vulkan;
    }
    auto device = gpu::makeDevice(backend);

    auto buf0 = device->createBuffer(gpu::BufferUsage::uniform,
                                     base::make_span<u8>(sizeof(count), (u8*)&count));
    auto buf1 = device->createBuffer(gpu::BufferUsage::storage,
                                     base::make_span<u8>(sizeof(arr1), (u8*)&arr1));
    auto buf2 = device->createBuffer(gpu::BufferUsage::storage,
                                     base::make_span<u8>(sizeof(arr2), (u8*)&arr2));
    auto buf3 =
        device->createBuffer(gpu::BufferUsage::storage | gpu::BufferUsage::map_read, sizeof(arr1));

    base::Optional<base::unique_ptr<resource::Resource>> blob;

    if (backend == gpu::DeviceKind::metal) {
        blob = resource_manager->open(resource::ResourceId("shader.metallib"));
    } else if (backend == gpu::DeviceKind::vulkan) {
        blob = resource_manager->open(resource::ResourceId("demo_sum.spirv"));
    }

    if (!blob.hasValue()) {
        spargel_log_fatal("cannot load shader code");
        return 1;
    }

    auto library = device->createShaderLibrary(blob.value()->getSpan());

    spargel_log_info("shader library loaded");

    auto pipeline = device->createComputePipeline2({
        .compute =
            {
                .library = library,
                .entry = "add_arrays",
            },
        .groups =
            {
                {
                    .stage = gpu::ShaderStage::compute,
                    .location = {.metal = {/* buffer id */ 0}, .vulkan = {/* set id */ 0}},
                    .arguments =
                        {
                            {.id = 0, .kind = gpu::BindEntryKind::uniform_buffer},
                            {.id = 1, .kind = gpu::BindEntryKind::storage_buffer},
                            {.id = 2, .kind = gpu::BindEntryKind::storage_buffer},
                            {.id = 3, .kind = gpu::BindEntryKind::storage_buffer},
                        },
                },
            },
    });

    spargel_log_info("pipeline created");

    auto bind_group = device->createBindGroup2(pipeline, 0);
    bind_group->setBuffer(0, buf0);
    bind_group->setBuffer(1, buf1);
    bind_group->setBuffer(2, buf2);
    bind_group->setBuffer(3, buf3);

    spargel_log_info("bind group prepared");

    // gpu::BindGroupLayoutBuilder builder;
    // builder.setStage(gpu::ShaderStage::compute);
    // builder.addEntry(0, gpu::BindEntryKind::uniform_buffer);  // control
    // builder.addEntry(1, gpu::BindEntryKind::storage_buffer);  // in1
    // builder.addEntry(2, gpu::BindEntryKind::storage_buffer);  // in2
    // builder.addEntry(3, gpu::BindEntryKind::storage_buffer);  // result
    // auto layout = builder.build(device.get());

    // auto pipeline = device->createComputePipeline({library, "add_arrays"}, {layout});
    // auto pipeline = device->createComputePipeline2(program);
    // auto max_size = pipeline->maxGroupSize();
    // spargel_log_info("maxGroupSize = %u", max_size);

    auto queue = device->createCommandQueue();

    auto cmdbuf = queue->createCommandBuffer();
    auto encoder = cmdbuf->beginComputePass();
    encoder->setComputePipeline2(pipeline);
    encoder->useBuffer(buf0, gpu::BufferAccess::read);
    encoder->useBuffer(buf1, gpu::BufferAccess::read);
    encoder->useBuffer(buf2, gpu::BufferAccess::read);
    encoder->useBuffer(buf3, gpu::BufferAccess::write);
    encoder->setBindGroup(0, bind_group);
    // encoder->setBuffer(buf0, {.apple = {.buffer_index = 0}});
    // encoder->setBuffer(buf1, {.apple = {.buffer_index = 1}});
    // encoder->setBuffer(buf2, {.apple = {.buffer_index = 2}});
    // encoder->setBuffer(buf3, {.apple = {.buffer_index = 3}});
    encoder->dispatch({.x = 1, .y = 1, .z = 1}, {.x = 64, .y = 1, .z = 1});
    cmdbuf->endComputePass(encoder);
    cmdbuf->submit();
    cmdbuf->wait();
    spargel_log_info("computation done!");
    float* result = (float*)buf3->mapAddr();
    for (int i = 0; i < 3; i++) {
        printf("%.1f ", result[i]);
    }
    putchar('\n');
    return 0;
}
