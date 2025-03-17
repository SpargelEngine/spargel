#include <spargel/base/logging.h>
#include <spargel/gpu/gpu.h>
#include <spargel/resource/directory.h>
#include <spargel/resource/resource.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>

// libc
#include <stdlib.h>

using namespace spargel;
using namespace spargel::gpu;

#define USE_VULKAN 0

#if SPARGEL_IS_MACOS
#define USE_METAL 1
#else
#define USE_METAL 0
#endif

struct vertex_shader_info {
    static constexpr VertexBufferLocation position_buffer = {
        .apple = {0},
        .vulkan = {0},
    };
    static constexpr VertexBufferLocation color_buffer = {
        .apple = {1},
        .vulkan = {1},
    };
    static constexpr VertexBufferLocation uniform_buffer = {
        .apple = {2},
        .vulkan = {2},
    };
};

struct fragment_shader_info {
    static constexpr VertexBufferLocation control_buffer = {
        .apple = {0},
        .vulkan = {0},
    };
    static constexpr VertexBufferLocation data_buffer = {
        .apple = {1},
        .vulkan = {1},
    };
};

struct VertexPosition {
    float x;
    float y;

    static VertexPosition randPosition() {
        if (rand() % 10 == 0) {
            return {
                rand() % 1000 - 500.0f,
                rand() % 1000 - 500.0f,
            };
        } else {
            return {
                float(rand() % 500),
                float(rand() % 500),
            };
        }
    }
};
struct VertexColor {
    float r;
    float g;
    float b;
    float a;
    static VertexColor randColor() {
        return {
            rand() % 255 / 255.0f,
            rand() % 255 / 255.0f,
            rand() % 255 / 255.0f,
            1.0f,
        };
    }
};

struct UniformData {
    struct {
        float width;
        float height;
    } viewport;
};

u32 max(u32 a, u32 b) { return a > b ? a : b; }

static constexpr int N = 100;

class Renderer final : public ui::WindowDelegate {
public:
    Renderer(ui::Window* window, resource::ResourceManager* resource_manager)
        : _window{window}, _manager{resource_manager} {
        _window->setDelegate(this);

#if USE_VULKAN
        _device = makeDevice(DeviceKind::vulkan);
#elif USE_METAL
        _device = makeDevice(DeviceKind::metal);
#endif

        _surface = _device->createSurface(_window);

#if USE_METAL
        auto blob = _manager->open(resource::ResourceId("shader.metallib"));

        _shader = _device->createShaderLibrary(blob.value()->getSpan());
#endif

        RenderPipelineBuilder builder;
        builder.setVertexShader(_shader, "tiles_vertex");
        builder.setFragmentShader(_shader, "tiles_fragment");
        builder.addVertexBuffer(sizeof(VertexPosition));
        builder.addVertexBuffer(sizeof(VertexColor));
        builder.addVertexAttribute(VertexAttributeFormat::float32x2, 0, 0, 0);
        builder.addVertexAttribute(VertexAttributeFormat::float32x4, 1, 1, 0);
        builder.addColorAttachment(TextureFormat::bgra8_unorm, false);
        _pipeline = builder.build(_device.get());

        for (int i = 0; i < N; i++) {
            _more_positions.push(VertexPosition::randPosition());
            _more_colors.push(VertexColor::randColor());
        }

        _positions = _device->createBuffer(
            BufferUsage::vertex,
            base::make_span<u8>(_more_positions.count() * sizeof(VertexPosition),
                                (u8*)_more_positions.data()));
        _colors = _device->createBuffer(
            BufferUsage::vertex, base::make_span<u8>(_more_colors.count() * sizeof(VertexColor),
                                                     (u8*)_more_colors.data()));

        _uniform_data.viewport.width = _surface->width();
        _uniform_data.viewport.height = _surface->height();
        _uniforms = _device->createBuffer(
            BufferUsage::uniform, base::make_span(sizeof(_uniform_data), (u8*)&_uniform_data));

        _frag_control = _device->createBuffer(BufferUsage::uniform, 64);
        _frag_data = _device->createBuffer(BufferUsage::uniform, 64);

        _queue = _device->createCommandQueue();

        _window->setAnimating(_animating);
        _window->requestRedraw();
    }

    ~Renderer() {
        // _device->destroyBuffer(_positions);
        // _device->destroyBuffer(_colors);
        // _device->destroyRenderPipeline(_pipeline);
        // _device->destroyShaderLibrary(_shader);
    }

    void onRender() override {
        auto texture = _surface->nextTexture();

        auto cmdbuf = _queue->createCommandBuffer();

        memset(_frag_data->mapAddr(), 0, 64);
        u32 batch = _frame << 10;
        memcpy(_frag_control->mapAddr(), &batch, sizeof(batch));

        auto encoder = cmdbuf->beginRenderPass({
            .color_attachments = {{
                .texture = texture,
                .clear_color = {0.0, 0.0, 0.0, 1.0},
            }},
        });

        encoder->setViewport({0, 0, _surface->width(), _surface->height(), 0, 1});

        encoder->setRenderPipeline(_pipeline);

        encoder->setVertexBuffer(_positions, vertex_shader_info::position_buffer);
        encoder->setVertexBuffer(_colors, vertex_shader_info::color_buffer);
        encoder->setVertexBuffer(_uniforms, vertex_shader_info::uniform_buffer);

        encoder->setFragmentBuffer(_frag_control, fragment_shader_info::control_buffer);
        encoder->setFragmentBuffer(_frag_data, fragment_shader_info::data_buffer);

        encoder->draw(0, N * 3);

        cmdbuf->endRenderPass(encoder);

        cmdbuf->present(_surface);

        cmdbuf->submit();

        cmdbuf->wait();

        _queue->destroyCommandBuffer(cmdbuf);

        if (_animating) {
            _frame++;
        }
    }

    void onKeyboard(ui::KeyboardEvent& e) override {
        if (e.toChar() == 'j') {
            _frame++;
        } else if (e.toChar() == 'k') {
            if (_frame > 0) _frame--;
        } else if (e.key == ui::PhysicalKey::space && e.action == ui::KeyboardAction::press) {
            _animating = !_animating;
            _window->setAnimating(_animating);
        }
        _window->requestRedraw();
    }

private:
    ui::Window* _window;
    resource::ResourceManager* _manager;
    base::unique_ptr<Device> _device;
    ObjectPtr<ShaderLibrary> _shader;
    ObjectPtr<RenderPipeline> _pipeline;
    ObjectPtr<Buffer> _positions;
    ObjectPtr<Buffer> _colors;
    UniformData _uniform_data;
    ObjectPtr<Buffer> _uniforms;
    ObjectPtr<Buffer> _frag_control;
    ObjectPtr<Buffer> _frag_data;
    ObjectPtr<Surface> _surface;
    ObjectPtr<CommandQueue> _queue;
    ObjectPtr<Texture> _atlas;
    base::vector<char> _str;
    bool _animating = false;
    usize _frame = 0;
    base::vector<VertexPosition> _more_positions;
    base::vector<VertexColor> _more_colors;
};

int main() {
    auto platform = ui::makePlatform();
    auto resource_manager = resource::makeRelativeManager(base::string("resources"));

    auto window = platform->makeWindow(500, 500);
    window->setTitle("Spargel Engine - GPU");

    Renderer r(window.get(), resource_manager.get());

    platform->startLoop();
    return 0;
}
