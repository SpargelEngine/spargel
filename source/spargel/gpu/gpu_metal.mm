#include <spargel/base/unique_ptr.h>
#include <spargel/gpu/gpu_metal.h>
#include <spargel/ui/window.h>

// metal
#import <Metal/Metal.h>

namespace spargel::gpu {

    namespace {

        // MTLCullMode translate_cull_mode(cull_mode mode) {
        //     using enum cull_mode;
        //     switch (mode) {
        //     case none:
        //         return MTLCullModeNone;
        //     case front:
        //         return MTLCullModeFront;
        //     case back:
        //         return MTLCullModeBack;
        //     }
        // }

        // MTLWinding translate_orientation(orientation o) {
        //     using enum orientation;
        //     switch (o) {
        //     case clockwise:
        //         return MTLWindingClockwise;
        //     case counter_clockwise:
        //         return MTLWindingCounterClockwise;
        //     }
        // }

        MTLPrimitiveTopologyClass translatePrimitiveType(PrimitiveKind kind) {
            using enum PrimitiveKind;
            switch (kind) {
            case point:
                return MTLPrimitiveTopologyClassPoint;
            case line:
                return MTLPrimitiveTopologyClassLine;
            case triangle:
                return MTLPrimitiveTopologyClassTriangle;
            }
        }

        MTLVertexStepFunction translateStepMode(VertexStepMode mode) {
            using enum VertexStepMode;
            switch (mode) {
            case vertex:
                return MTLVertexStepFunctionPerVertex;
            case instance:
                return MTLVertexStepFunctionPerInstance;
            }
        }

        MTLVertexFormat translateVertexFormat(VertexAttributeFormat format) {
            using enum VertexAttributeFormat;
            switch (format) {
            case float32x2:
                return MTLVertexFormatFloat2;
            case float32x4:
                return MTLVertexFormatFloat4;
            default:
                spargel_panic_here();
            }
        }

        MTLLoadAction translate_load_action(LoadAction action) {
            using enum LoadAction;
            switch (action) {
            case load:
                return MTLLoadActionLoad;
            case clear:
                return MTLLoadActionClear;
            case dont_care:
                return MTLLoadActionDontCare;
            }
        }

        MTLStoreAction translate_store_action(StoreAction action) {
            using enum StoreAction;
            switch (action) {
            case store:
                return MTLStoreActionStore;
            case dont_care:
                return MTLStoreActionDontCare;
            }
        }

        MTLPixelFormat translatePixelFormat(TextureFormat format) {
            using enum TextureFormat;
            switch (format) {
            case bgra8_unorm:
                return MTLPixelFormatBGRA8Unorm;
            default:
                spargel_panic_here();
            }
        }

        MTLResourceUsage translateBufferAccess(BufferAccess access) {
            MTLResourceUsage result = 0;
#define _TRANSLATE(x, y)               \
    if (access.has(BufferAccess::x)) { \
        result |= y;                   \
    }
            _TRANSLATE(read, MTLResourceUsageRead);
            _TRANSLATE(write, MTLResourceUsageWrite);
#undef _TRANSLATE
            return result;
        }

    }  // namespace

    base::unique_ptr<Device> make_device_metal() { return base::make_unique<DeviceMetal>(); }

    DeviceMetal::DeviceMetal() : Device(DeviceKind::metal) {
        _device = MTLCreateSystemDefaultDevice();  // ns_returns_retained
        [_device retain];
    }

    DeviceMetal::~DeviceMetal() { [_device release]; }

    ObjectPtr<ShaderLibrary> DeviceMetal::createShaderLibrary(base::span<u8> bytes) {
        // dispatch create a copy of the data
        //
        // notes:
        // This object is retained initially. It is your responsibility to release the data object
        // when you are done using it.
        //
        auto library_data =
            dispatch_data_create(bytes.data(), bytes.count(), dispatch_get_main_queue(),
                                 DISPATCH_DATA_DESTRUCTOR_DEFAULT);
        NSError* error;
        auto library = [_device newLibraryWithData:library_data error:&error];
        if (library == nil) {
            return nullptr;
        }
        return make_object<ShaderLibraryMetal>(library_data, library);
    }

    ObjectPtr<RenderPipeline> DeviceMetal::createRenderPipeline(
        RenderPipelineDescriptor const& descriptor) {
        auto desc = [[MTLRenderPipelineDescriptor alloc] init];

        auto vertex_library = descriptor.vertex_shader.library.cast<ShaderLibraryMetal>();
        auto vertex_entry = descriptor.vertex_shader.entry;

        auto vertex_function = [vertex_library->library()
            newFunctionWithName:[NSString stringWithUTF8String:vertex_entry]];

        auto vertex_descriptor = [MTLVertexDescriptor vertexDescriptor];

        for (ssize i = 0; i < descriptor.vertex_buffers.count(); i++) {
            vertex_descriptor.layouts[i].stepFunction =
                translateStepMode(descriptor.vertex_buffers[i].step_mode);
            vertex_descriptor.layouts[i].stride = descriptor.vertex_buffers[i].stride;
        }

        for (ssize i = 0; i < descriptor.vertex_attributes.count(); i++) {
            vertex_descriptor.attributes[i].format =
                translateVertexFormat(descriptor.vertex_attributes[i].format);
            vertex_descriptor.attributes[i].offset = descriptor.vertex_attributes[i].offset;
            // TODO: fix
            vertex_descriptor.attributes[i].bufferIndex = descriptor.vertex_attributes[i].buffer;
        }

        desc.vertexFunction = vertex_function;

        for (usize i = 0; i < descriptor.color_attachments.count(); i++) {
            desc.colorAttachments[i].pixelFormat =
                translatePixelFormat(descriptor.color_attachments[i].format);
            desc.colorAttachments[i].blendingEnabled = descriptor.color_attachments[i].enable_blend;
            desc.colorAttachments[i].alphaBlendOperation = MTLBlendOperationAdd;
            desc.colorAttachments[i].rgbBlendOperation = MTLBlendOperationAdd;
            desc.colorAttachments[i].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
            desc.colorAttachments[i].sourceAlphaBlendFactor = MTLBlendFactorOne;
            desc.colorAttachments[i].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
            desc.colorAttachments[i].destinationAlphaBlendFactor = MTLBlendFactorOne;
        }

        desc.vertexDescriptor = vertex_descriptor;
        desc.inputPrimitiveTopology = translatePrimitiveType(descriptor.primitive);

        auto frag_library = descriptor.fragment_shader.library.cast<ShaderLibraryMetal>();
        auto frag_entry = descriptor.fragment_shader.entry;

        auto frag_function = [frag_library->library()
            newFunctionWithName:[NSString stringWithUTF8String:frag_entry]];

        for (MTLAttribute* attr in frag_function.stageInputAttributes) {
            NSLog(@"%@", attr);
        }

        desc.fragmentFunction = frag_function;

        NSError* error;

        auto state = [_device newRenderPipelineStateWithDescriptor:desc error:&error];

        [desc release];

        return make_object<RenderPipelineMetal>(vertex_function, state);
    }

    ObjectPtr<Buffer> DeviceMetal::createBuffer([[maybe_unused]] BufferUsage usage,
                                                base::span<u8> bytes) {
        auto buf = [_device newBufferWithBytes:bytes.data()
                                        length:bytes.count()
                                       options:MTLResourceStorageModeShared];
        return make_object<BufferMetal>(buf);
    }

    ObjectPtr<Buffer> DeviceMetal::createBuffer([[maybe_unused]] BufferUsage usage, u32 size) {
        auto buf = [_device newBufferWithLength:size options:MTLResourceStorageModeShared];
        return make_object<BufferMetal>(buf);
    }

    ObjectPtr<Surface> DeviceMetal::createSurface(ui::Window* w) {
        CAMetalLayer* l = (CAMetalLayer*)w->getHandle().apple.layer;
        l.device = _device;
        return make_object<SurfaceMetal>(l);
    }

    void DeviceMetal::destroyShaderLibrary(ObjectPtr<ShaderLibrary> l) {
        auto library = l.cast<ShaderLibraryMetal>();
        destroy_object(library);
    }

    void DeviceMetal::destroyRenderPipeline(ObjectPtr<RenderPipeline> p) {
        auto pipeline = p.cast<RenderPipelineMetal>();
        destroy_object(pipeline);
    }

    void DeviceMetal::destroyBuffer(ObjectPtr<Buffer> b) {
        auto buf = b.cast<BufferMetal>();
        destroy_object(buf);
    }

    ObjectPtr<CommandQueue> DeviceMetal::createCommandQueue() {
        return make_object<CommandQueueMetal>([_device newCommandQueue]);
    }

    void DeviceMetal::destroyCommandQueue(ObjectPtr<CommandQueue> q) {
        destroy_object(q.cast<CommandQueueMetal>());
    }

    ObjectPtr<Texture> DeviceMetal::createTexture(u32 width, u32 height) {
        auto desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatA8Unorm
                                                                       width:width
                                                                      height:height
                                                                   mipmapped:NO];
        desc.storageMode = MTLStorageModeShared;
        auto texture = [_device newTextureWithDescriptor:desc];
        return make_object<TextureMetal>(texture);
    }

    void DeviceMetal::destroyTexture(ObjectPtr<Texture> texture) {
        // todo
    }

    ShaderLibraryMetal::ShaderLibraryMetal(dispatch_data_t data, id<MTLLibrary> library)
        : _data{data}, _library{library} {}

    ShaderLibraryMetal::~ShaderLibraryMetal() {
        [_library release];
        [_data release];
    }

    RenderPipelineMetal::RenderPipelineMetal(id<MTLFunction> vertex,
                                             id<MTLRenderPipelineState> pipeline)
        : _vertex{vertex}, _pipeline{pipeline} {}

    RenderPipelineMetal::~RenderPipelineMetal() {
        [_pipeline release];
        [_vertex release];
    }

    BufferMetal::BufferMetal(id<MTLBuffer> b) : _buffer{b} {}

    BufferMetal::~BufferMetal() { [_buffer release]; }

    ObjectPtr<CommandBuffer> CommandQueueMetal::createCommandBuffer() {
        return make_object<CommandBufferMetal>([_queue commandBuffer]);
    }

    void CommandQueueMetal::destroyCommandBuffer(ObjectPtr<CommandBuffer> cmdbuf) {
        destroy_object(cmdbuf.cast<CommandBufferMetal>());
    }

    ObjectPtr<RenderPassEncoder> CommandBufferMetal::beginRenderPass(
        RenderPassDescriptor const& descriptor) {
        auto desc = [MTLRenderPassDescriptor renderPassDescriptor];
        for (usize i = 0; i < descriptor.color_attachments.count(); i++) {
            desc.colorAttachments[i].texture =
                descriptor.color_attachments[i].texture.cast<TextureMetal>()->texture();
            desc.colorAttachments[i].loadAction =
                translate_load_action(descriptor.color_attachments[i].load);
            desc.colorAttachments[i].storeAction =
                translate_store_action(descriptor.color_attachments[i].store);
            auto& c = descriptor.color_attachments[i].clear_color;
            desc.colorAttachments[i].clearColor = MTLClearColorMake(c.r, c.g, c.b, c.a);
        }
        return make_object<RenderPassEncoderMetal>(
            [_cmdbuf renderCommandEncoderWithDescriptor:desc]);
    }

    void CommandBufferMetal::endRenderPass(ObjectPtr<RenderPassEncoder> e) {
        auto encoder = e.cast<RenderPassEncoderMetal>();
        [encoder->encoder() endEncoding];
        destroy_object(encoder);
    }

    void CommandBufferMetal::present(ObjectPtr<Surface> s) {
        [_cmdbuf presentDrawable:s.cast<SurfaceMetal>()->drawable()];
    }

    void CommandBufferMetal::submit() { [_cmdbuf commit]; }

    ObjectPtr<ComputePassEncoder> CommandBufferMetal::beginComputePass() {
        return make_object<ComputePassEncoderMetal>([_cmdbuf computeCommandEncoder]);
    }

    void CommandBufferMetal::endComputePass(ObjectPtr<ComputePassEncoder> e) {
        auto encoder = e.cast<ComputePassEncoderMetal>();
        [encoder->encoder() endEncoding];
        destroy_object(encoder);
    }

    void RenderPassEncoderMetal::setRenderPipeline(ObjectPtr<RenderPipeline> p) {
        [_encoder setRenderPipelineState:p.cast<RenderPipelineMetal>()->pipeline()];
    }
    void RenderPassEncoderMetal::setVertexBuffer(ObjectPtr<Buffer> b,
                                                 VertexBufferLocation const& loc) {
        [_encoder setVertexBuffer:b.cast<BufferMetal>()->buffer()
                           offset:0
                          atIndex:loc.apple.buffer_index];
    }
    void RenderPassEncoderMetal::setTexture(ObjectPtr<Texture> texture) {
        // todo: index
        [_encoder setFragmentTexture:texture.cast<TextureMetal>()->texture() atIndex:0];
    }
    void RenderPassEncoderMetal::setViewport(Viewport v) {
        [_encoder setViewport:{v.x, v.y, v.width, v.height, v.z_near, v.z_far}];
    }
    void RenderPassEncoderMetal::draw(int vertex_start, int vertex_count) {
        [_encoder drawPrimitives:MTLPrimitiveTypeTriangle
                     vertexStart:vertex_start
                     vertexCount:vertex_count];
    }
    void RenderPassEncoderMetal::draw(int vertex_start, int vertex_count, int instance_start,
                                      int instance_count) {
        [_encoder drawPrimitives:MTLPrimitiveTypeTriangle
                     vertexStart:vertex_start
                     vertexCount:vertex_count
                   instanceCount:instance_count
                    baseInstance:instance_start];
    }

    void TextureMetal::updateRegion(u32 x, u32 y, u32 width, u32 height, u32 bytes_per_row,
                                    base::span<base::Byte> bytes) {
        [_texture replaceRegion:MTLRegionMake2D(x, y, width, height)
                    mipmapLevel:0
                      withBytes:bytes.data()
                    bytesPerRow:bytes_per_row];
    }

    void ComputePassEncoderMetal::setBindGroup(u32 index, ObjectPtr<BindGroup> g) {
        auto group = g.cast<BindGroupMetal>();
        [_encoder setBuffer:group->buffer() offset:0 atIndex:group->program()->getBufferId(index)];
    }

    void ComputePassEncoderMetal::setComputePipeline2(ObjectPtr<ComputePipeline2> pipeline) {
        [_encoder setComputePipelineState:pipeline.cast<ComputePipeline2Metal>()->pipeline()];
    }

    void ComputePassEncoderMetal::useBuffer(ObjectPtr<Buffer> buffer, BufferAccess access) {
        [_encoder useResource:buffer.cast<BufferMetal>()->buffer()
                        usage:translateBufferAccess(access)];
    }

    ObjectPtr<RenderPipeline2> DeviceMetal::createRenderPipeline2(
        RenderPipeline2Descriptor const& descriptor) {
        auto desc = [[MTLRenderPipelineDescriptor alloc] init];

        auto vertex_library = descriptor.vertex_shader.library.cast<ShaderLibraryMetal>();
        auto vertex_entry = descriptor.vertex_shader.entry;

        auto vertex_function = [vertex_library->library()
            newFunctionWithName:[NSString stringWithUTF8String:vertex_entry]];

        auto vertex_descriptor = [MTLVertexDescriptor vertexDescriptor];

        for (ssize i = 0; i < descriptor.vertex_buffers.count(); i++) {
            vertex_descriptor.layouts[i].stepFunction =
                translateStepMode(descriptor.vertex_buffers[i].step_mode);
            vertex_descriptor.layouts[i].stride = descriptor.vertex_buffers[i].stride;
        }

        for (ssize i = 0; i < descriptor.vertex_attributes.count(); i++) {
            vertex_descriptor.attributes[i].format =
                translateVertexFormat(descriptor.vertex_attributes[i].format);
            vertex_descriptor.attributes[i].offset = descriptor.vertex_attributes[i].offset;
            // TODO: fix
            vertex_descriptor.attributes[i].bufferIndex = descriptor.vertex_attributes[i].buffer;
        }

        desc.vertexFunction = vertex_function;

        for (usize i = 0; i < descriptor.color_attachments.count(); i++) {
            desc.colorAttachments[i].pixelFormat =
                translatePixelFormat(descriptor.color_attachments[i].format);
            desc.colorAttachments[i].blendingEnabled = descriptor.color_attachments[i].enable_blend;
            desc.colorAttachments[i].alphaBlendOperation = MTLBlendOperationAdd;
            desc.colorAttachments[i].rgbBlendOperation = MTLBlendOperationAdd;
            desc.colorAttachments[i].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
            desc.colorAttachments[i].sourceAlphaBlendFactor = MTLBlendFactorOne;
            desc.colorAttachments[i].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
            desc.colorAttachments[i].destinationAlphaBlendFactor = MTLBlendFactorOne;
        }

        desc.vertexDescriptor = vertex_descriptor;
        desc.inputPrimitiveTopology = translatePrimitiveType(descriptor.primitive);

        auto frag_library = descriptor.fragment_shader.library.cast<ShaderLibraryMetal>();
        auto frag_entry = descriptor.fragment_shader.entry;

        auto frag_function = [frag_library->library()
            newFunctionWithName:[NSString stringWithUTF8String:frag_entry]];

        for (MTLAttribute* attr in frag_function.stageInputAttributes) {
            NSLog(@"%@", attr);
        }

        desc.fragmentFunction = frag_function;

        NSError* error;

        auto state = [_device newRenderPipelineStateWithDescriptor:desc error:&error];

        [desc release];

        return make_object<RenderPipeline2Metal>(vertex_function, frag_function, state, descriptor.groups);
    }

}  // namespace spargel::gpu
