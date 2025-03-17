#include <spargel/base/logging.h>
#include <spargel/gpu/gpu.h>
#include <spargel/resource/directory.h>
#include <spargel/resource/resource.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/ui_mac.h>
#include <spargel/ui/window.h>

using namespace spargel;
using namespace spargel::gpu;

#define USE_VULKAN 1
#if SPARGEL_IS_MACOS
#define USE_METAL 1
#else
#define USE_METAL 0
#endif

// #if USE_METAL
// #include <spargel/gpu/demo/shader.metallib.inc>
// #endif

// #if USE_VULKAN
// #include <spargel/gpu/demo/fragment_shader.spirv.inc>
// #include <spargel/gpu/demo/vertex_shader.spirv.inc>
// #endif

#include <stdio.h>

struct vertex_shader_info {
    static constexpr VertexBufferLocation position_buffer = {
        .apple = {0},
        .vulkan = {0},
    };
    static constexpr VertexBufferLocation quad_buffer = {
        .apple = {1},
        .vulkan = {1},
    };
    static constexpr VertexBufferLocation uniform_buffer = {
        .apple = {2},
        .vulkan = {2},
    };
};

struct VertexPosition {
    float x;
    float y;
};
struct VertexColor {
    float r;
    float g;
    float b;
    float a;
};

static constexpr VertexPosition positions[] = {
    {0, 0}, {1, 0}, {1, 1}, {1, 1}, {0, 1}, {0, 0},
};

struct UniformData {
    struct {
        float width;
        float height;
    } viewport;
};

struct QuadData {
    struct {
        float x;
        float y;
    } origin;
    struct {
        float width;
        float height;
    } size;
    struct {
        float x;
        float y;
    } cell_origin;
};

u32 max(u32 a, u32 b) { return a > b ? a : b; }

class Renderer final : public ui::WindowDelegate, public ui::TextInputDelegate {
public:
    Renderer(ui::WindowAppKit* window, resource::ResourceManager* resource_manager,
             ui::TextSystem* text_system)
        : _window{window}, _manager{resource_manager}, _text_system{text_system} {
        _window->setDelegate(this);
        _window->setTextDelegate(this);

        _device = makeDevice(DeviceKind::metal);

        _surface = _device->createSurface(_window);

#if USE_METAL
        auto blob = _manager->open(resource::ResourceId("shader.metallib"));

        _shader = _device->createShaderLibrary(blob.value()->getSpan());

        // TODO: Close the resource.
        // blob->close();
#endif

        RenderPipelineBuilder builder;
        builder.setVertexShader(_shader, "vertex_shader");
        builder.setFragmentShader(_shader, "fragment_shader");
        builder.addVertexBuffer(sizeof(VertexPosition));
        builder.addVertexAttribute(VertexAttributeFormat::float32x2, 0, 0, 0);
        builder.addColorAttachment(TextureFormat::bgra8_unorm, true);
        _pipeline = builder.build(_device.get());

        _positions = _device->createBuffer(BufferUsage::vertex,
                                           base::make_span<u8>(sizeof(positions), (u8*)positions));

        _uniform_data.viewport.width = _surface->width();
        _uniform_data.viewport.height = _surface->height();
        _uniforms = _device->createBuffer(
            BufferUsage::uniform, base::make_span(sizeof(_uniform_data), (u8*)&_uniform_data));

        _queue = _device->createCommandQueue();

        _atlas = _device->createTexture(512, 512);

        // _str.push('t');
        //

        // Arabia
        // _str.push(0xd9);
        // _str.push(0x84);
        // _str.push(0xd8);
        // _str.push(0xa7);

        // Arabia
        // _str.push(0xd9);
        // _str.push(0x85);
        // _str.push(0xd8);
        // _str.push(0xaa);
        // _str.push(0xd8);
        // _str.push(0xb3);
        // _str.push(0xd8);
        // _str.push(0xa7);
        // _str.push(0xd9);
        // _str.push(0x88);
        // _str.push(0xd9);
        // _str.push(0x8a);
        // _str.push(0xd9);
        // _str.push(0x86);

        // _str.push(0xe2);
        // _str.push(0x9d);
        // _str.push(0xa4);
        // _str.push(0xef);
        // _str.push(0xb8);
        // _str.push(0x8f);

        // _str.push(0xf0);
        // _str.push(0x9f);
        // _str.push(0x98);
        // _str.push(0x80);

        // _str.push(0xf0);
        // _str.push(0x9f);
        // _str.push(0x96);
        // _str.push(0x90);
        // _str.push(0xef);
        // _str.push(0xb8);
        // _str.push(0x8f);
        //

        _window->setAnimating(_animating);
        _window->requestRedraw();
    }

    ~Renderer() {
        _device->destroyBuffer(_positions);
        _device->destroyRenderPipeline(_pipeline);
        _device->destroyShaderLibrary(_shader);
    }

    void onRender() override {
        // spargel_log_info("%lu", _glyph_cache.count());

        auto layout_result = _text_system->layoutLine(base::string_view(_str.begin(), _str.end()));

        _vquads.clear();
        float total_width = 0;
        for (usize r = 0; r < layout_result.runs.count(); r++) {
            auto& run = layout_result.runs[r];
            for (usize i = 0; i < run.glyphs.count(); i++) {
                printf("%.1f ", run.positions[i].x);
                auto& info = findOrInsert(run.glyphs[i]);
                QuadData quad;
                quad.origin.x = total_width + run.positions[i].x;
                quad.origin.y = info.descent + run.positions[i].y;
                // quad.size.width = info.width - 1;
                quad.size.width = info.width - 1;
                quad.size.height = info.height;
                quad.cell_origin.x = info.x + 1;
                quad.cell_origin.y = info.y + 1;
                _vquads.push(quad);
            }
            printf("\n");
            total_width += run.width;
        }
        // todo: use uniform
        float half_width = total_width / 2;
        for (usize i = 0; i < _vquads.count(); i++) {
            _vquads[i].origin.x -= half_width;
        }
        _quads = _device->createBuffer(
            BufferUsage::storage,
            base::make_span(_vquads.count() * sizeof(QuadData), (u8*)_vquads.data()));

        auto texture = _surface->nextTexture();

        auto cmdbuf = _queue->createCommandBuffer();

        auto encoder = cmdbuf->beginRenderPass({
            .color_attachments = {{
                .texture = texture,
                .clear_color = {0.0, 0.0, 0.0, 1.0},
            }},
        });

        encoder->setViewport({0, 0, _surface->width(), _surface->height(), 0, 1});
        encoder->setRenderPipeline(_pipeline);
        encoder->setVertexBuffer(_positions, vertex_shader_info::position_buffer);
        encoder->setVertexBuffer(_uniforms, vertex_shader_info::uniform_buffer);
        encoder->setVertexBuffer(_quads, vertex_shader_info::quad_buffer);
        encoder->setTexture(_atlas);
        encoder->draw(0, 6, 0, _vquads.count());

        cmdbuf->endRenderPass(encoder);

        cmdbuf->present(_surface);

        cmdbuf->submit();

        _queue->destroyCommandBuffer(cmdbuf);
        _device->destroyBuffer(_quads);

        _valid = [[NSArray alloc] init];
    }

    void onKeyboard(ui::KeyboardEvent& e) override {
        if (e.key == ui::PhysicalKey::key_delete && e.action == ui::KeyboardAction::press) {
            _str.pop();
            if (!_animating) {
                _window->requestRedraw();
            }
        } else if (e.key == ui::PhysicalKey::space && e.action == ui::KeyboardAction::press) {
            _animating = !_animating;
            _window->setAnimating(_animating);
        } else {
            _str.push(e.toChar());
            if (!_animating) {
                _window->requestRedraw();
            }
        }
        // [[NSTextInputContext currentInputContext] invalidateCharacterCoordinates];
    }

    // TextInputDelegate
    bool hasMarkedText() override {
        spargel_log_info("hasMarkedText");
        return false;
    }
    void setMarkedText(id string, NSRange selected, NSRange replaced) override {
        spargel_log_info("setMarkedText");
    }
    NSRange getMarkedRange() override {
        spargel_log_info("getMarkedRange");
        return NSMakeRange(NSNotFound, 0);
    }
    void unmarkText() override { spargel_log_info("unmarkText"); }
    NSArray<NSAttributedStringKey>* validAttributesForMarkedText() override {
        spargel_log_info("validAttributesForMarkedText");
        // return _valid;
        return [NSArray array];
    }
    NSRange getSelectedRange() override {
        spargel_log_info("getSelectedRange");
        return NSMakeRange(_str.count(), 0);
    }
    void insertText(id string, NSRange replaced) override { spargel_log_info("insertText"); }
    NSRect firstRectForCharacterRange(NSRange range, NSRangePointer actual) override {
        spargel_log_info("firstRectForCharacterRange");
        printf("range = (%lu, %lu)", static_cast<unsigned long>(range.location),
               static_cast<unsigned long>(range.length));
        if (actual != nullptr) {
            printf(" actual = (%lu, %lu)", (unsigned long)(actual->location),
                   (unsigned long)(actual->length));
        }
        putchar('\n');
        if (actual != nullptr) {
            return NSMakeRect(50 + _str.count() * 20, 50, 0, 20);
        }
        return NSMakeRect(50, 50, _str.count() * 20, 20);
    }
    NSAttributedString* attributedSubstringForProposedRange(NSRange range,
                                                            NSRangePointer actual) override {
        spargel_log_info("attributedSubstringForProposedRange");
        return nil;
    }
    NSUInteger characterIndexForPoint(NSPoint point) override {
        spargel_log_info("characterIndexForPoint");
        return 0;
    }

private:
    struct GlyphEntry {
        ui::GlyphId id;
        u32 x;
        u32 y;
        u32 width;
        u32 height;
        float glyph_width;
        float glyph_height;
        float descent;
    };

    // todo: optimize
    GlyphEntry& findOrInsert(ui::GlyphId id) {
        for (usize i = 0; i < _glyph_cache.count(); i++) {
            if (_glyph_cache[i].id == id) {
                return _glyph_cache[i];
            }
        }
        // not found
        auto raster = _text_system->rasterizeGlyph(id);
        auto& bitmap = raster.bitmap;
        // try to insert
        if (_cur_col + bitmap.width >= 512) {
            // next row
            _cur_row = _nxt_row;
            _cur_col = 0;
        }
        u32 x = _cur_col;
        _cur_col += bitmap.width;
        _nxt_row = max(_nxt_row, _cur_row + bitmap.height);
        if (_nxt_row >= 512) {
            spargel_log_fatal("glyph atlas out of space!");
            spargel_panic_here();
        }
        u32 y = _cur_row;
        _glyph_cache.push(id, x, y, bitmap.width, bitmap.height, raster.glyph_width,
                          raster.glyph_height, raster.descent);
        _atlas->updateRegion(x, y, bitmap.width, bitmap.height, bitmap.width,
                             bitmap.data.toSpan().asBytes());

        // for (usize i = 0; i < bitmap.height; i++) {
        //     for (usize j = 0; j < bitmap.width; j++) {
        //         if (bitmap.data[i * bitmap.width + j] != 0x3f) {
        //             putchar('X');
        //         } else {
        //             putchar('.');
        //         }
        //     }
        //     putchar('\n');
        // }

        return _glyph_cache[_glyph_cache.count() - 1];
    }

    ui::WindowAppKit* _window;
    resource::ResourceManager* _manager;
    ui::TextSystem* _text_system;
    base::unique_ptr<Device> _device;
    ObjectPtr<ShaderLibrary> _shader;
    ObjectPtr<RenderPipeline> _pipeline;
    ObjectPtr<Buffer> _positions;
    UniformData _uniform_data;
    ObjectPtr<Buffer> _uniforms;
    ObjectPtr<Buffer> _quads;
    ObjectPtr<Surface> _surface;
    ObjectPtr<CommandQueue> _queue;
    ObjectPtr<Texture> _atlas;
    base::vector<char> _str;
    base::vector<QuadData> _vquads;
    base::vector<GlyphEntry> _glyph_cache;
    u32 _cur_row = 0;
    u32 _cur_col = 0;
    u32 _nxt_row = 0;
    bool _animating = false;
    NSArray<NSString*>* _valid;
};

int main() {
    auto platform = ui::makePlatform();
    auto resource_manager = resource::makeRelativeManager(base::string("resources"));
    auto text_system = platform->createTextSystem();

    auto window = platform->makeWindow(500, 500);
    window->setTitle("Spargel Engine - GPU");

    Renderer r((ui::WindowAppKit*)window.get(), resource_manager.get(), text_system.get());

    platform->startLoop();
    return 0;
}
