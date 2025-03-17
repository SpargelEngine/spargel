#include <spargel/base/logging.h>
#include <spargel/entry/simple.h>
#include <spargel/gpu/gpu.h>
#include <spargel/gpu/gpu_metal.h>
#include <spargel/gpu/gpu_vulkan.h>
#include <spargel/ui/ui.h>

/* libc */
#include <math.h>

using namespace spargel;

#define USE_VULKAN 1
#if SPARGEL_IS_MACOS
#define USE_METAL 1
#else
#define USE_METAL 0
#endif

struct Renderer final : ui::window_delegate {
    void on_render() override {
        gpu::reset_command_buffer(device, cmdbuf);

        gpu::presentable_id presentable;
        gpu::texture_id texture;
        struct gpu::acquire_descriptor adesc = {.swapchain = swapchain};
        gpu::acquire_image(device, &adesc, &presentable);
        gpu::presentable_texture(device, presentable, &texture);
        gpu::render_pass_encoder_id encoder;
        struct gpu::render_pass_descriptor rpdesc = {
            .command_buffer = cmdbuf,
            .color_attachment = texture,
            .clear_color = {fabs(sin(frame / 120.f + 72)), fabs(sin(frame / 120.f + 36)),
                            fabs(sin(frame / 120.f)), 1.0},
            .swapchain = swapchain,
        };
        gpu::begin_render_pass(device, &rpdesc, &encoder);
        gpu::end_render_pass(device, encoder);
        {
            struct gpu::present_descriptor desc = {
                .command_buffer = cmdbuf,
                .presentable = presentable,
            };
            gpu::present(device, &desc);
        }
        frame++;
    }

    gpu::device_id device;
    gpu::surface_id surface;
    gpu::swapchain_id swapchain;
    gpu::command_queue_id queue;
    gpu::command_buffer_id cmdbuf;
    base::unique_ptr<ui::window> window;
    int frame;
};

static int create(int backend, char const* title, Renderer* r, ui::platform* platform,
                  base::unique_ptr<ui::window> window) {
    window->set_title(title);
    window->set_delegate(r);

    int result;

    gpu::device_id device;
    {
        struct gpu::device_descriptor desc = {
            .backend = gpu::BACKEND_VULKAN,
            .platform = platform->kind(),
        };
        result = gpu::create_default_device(&desc, &device);
    }
    if (result != 0) return 1;
    spargel_log_info("device created");

    gpu::command_queue_id queue;
    result = gpu::create_command_queue(device, &queue);
    if (result != 0) return 1;
    spargel_log_info("command queue created");

    gpu::surface_id surface;
    {
        struct gpu::surface_descriptor desc = {
            .window = window.get(),
        };
        result = gpu::create_surface(device, &desc, &surface);
    }
    if (result != 0) return 1;
    spargel_log_info("surface created");

    gpu::swapchain_id swapchain;
    {
        struct gpu::swapchain_descriptor desc = {
            .surface = surface,
            .width = 500,
            .height = 500,
        };
        result = gpu::create_swapchain(device, &desc, &swapchain);
    }
    if (result != 0) return 1;
    spargel_log_info("swapchain created");

    gpu::command_buffer_id cmdbuf;
    {
        struct gpu::command_buffer_descriptor desc = {
            .queue = queue,
        };
        result = gpu::create_command_buffer(device, &desc, &cmdbuf);
    }
    if (result != 0) return 1;
    spargel_log_info("command buffer created");

    r->device = device;
    r->queue = queue;
    r->surface = surface;
    r->swapchain = swapchain;
    r->cmdbuf = cmdbuf;
    r->frame = 0;
    r->window = base::move(window);

    return 0;
}

int entry::simple_entry(entry::simple_entry_data* data) {
    auto platform = base::move(data->platform);

#if USE_VULKAN
    Renderer r_vk;
    if (create(gpu::BACKEND_VULKAN, "Spargel Demo - Vulkan", &r_vk, platform.get(),
               base::move(data->window)) != 0)
        return 1;
#endif
#if USE_METAL
    Renderer r_mtl;
    if (create(gpu::BACKEND_VULKAN, "Spargel Demo - Metal", &r_mtl, platform.get(),
               base::move(data->window)) != 0)
        return 1;
#endif

    platform->start_loop();
    return 0;
}
