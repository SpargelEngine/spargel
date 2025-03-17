#include <spargel/ui/ui_dummy.h>

namespace spargel::ui {

    LineLayout TextSystemDummy::layoutLine(base::string_view str) {
        LineLayout layout;
        LayoutRun run;
        run.width = static_cast<float>(str.length()) * 10.0f;  // Dummy width
        layout.runs.push(run);
        return layout;
    }

    RasterResult TextSystemDummy::rasterizeGlyph(GlyphId id) {
        RasterResult result;
        result.bitmap.width = 10;
        result.bitmap.height = 10;
        result.bitmap.data.resize(10 * 10, 0xFF);  // White square
        result.glyph_width = 10.0f;
        result.glyph_height = 10.0f;
        result.descent = 2.0f;
        return result;
    }

    base::unique_ptr<Platform> makePlatformDummy() { return base::make_unique<PlatformDummy>(); }

}  // namespace spargel::ui
