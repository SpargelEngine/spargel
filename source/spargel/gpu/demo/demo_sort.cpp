#include <spargel/base/command_line.h>
#include <spargel/gpu/gpu.h>
#include <spargel/resource/directory.h>

//
#include <stdio.h>
#include <stdlib.h>

using namespace spargel;

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

    base::vector<u32> data;
    data.reserve(16);
    data.set_count(16);
    for (usize i = 0; i < 16; i++) {
        data[i] = rand() % 20;
        printf("%u ", data[i]);
    }
    putchar('\n');

    auto buf0 =
        device->createBuffer(gpu::BufferUsage::storage,
                             base::make_span<u8>(sizeof(u32) * data.count(), (u8*)data.data()));

    base::Optional<base::unique_ptr<resource::Resource>> blob;

    if (backend == gpu::DeviceKind::metal) {
        blob = resource_manager->open(resource::ResourceId("shader.metallib"));
    } else if (backend == gpu::DeviceKind::vulkan) {
        blob = resource_manager->open(resource::ResourceId("demo_sort.spirv"));
    }
    auto library = device->createShaderLibrary(blob.value()->getSpan());

    auto pipeline = device->createComputePipeline2({
        .compute =
            {
                .library = library,
                .entry = "bitonic_sort",
            },
        .groups =
            {
                {
                    .stage = gpu::ShaderStage::compute,
                    .location = {.metal = {/* buffer id */ 0}, .vulkan = {/* set id */ 0}},
                    .arguments =
                        {
                            {.id = 0, .kind = gpu::BindEntryKind::storage_buffer},
                        },
                },
            },
    });

    auto bind_group = device->createBindGroup2(pipeline, 0);
    bind_group->setBuffer(0, buf0);

    auto queue = device->createCommandQueue();

    auto cmdbuf = queue->createCommandBuffer();

    auto encoder = cmdbuf->beginComputePass();
    encoder->setComputePipeline2(pipeline);
    encoder->useBuffer(buf0, gpu::BufferAccess::read_write);
    encoder->setBindGroup(0, bind_group);
    encoder->dispatch({.x = 1, .y = 1, .z = 1}, {.x = 8, .y = 1, .z = 1});
    cmdbuf->endComputePass(encoder);

    cmdbuf->submit();

    cmdbuf->wait();

    auto result = (u32*)buf0->mapAddr();
    for (int i = 0; i < 16; i++) {
        printf("%u ", result[i]);
    }
    putchar('\n');

    return 0;
}
