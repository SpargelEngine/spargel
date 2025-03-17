#pragma once

#include <spargel/base/string_view.h>
#include <spargel/base/vector.h>

namespace spargel::ui {

    struct Bitmap {
        usize width;
        usize height;
        base::vector<u8> data;
    };

    using GlyphId = u32;
    struct GlyphPosition {
        float x;
        float y;
    };

    struct LayoutRun {
        // TODO: font id
        base::vector<GlyphId> glyphs;
        base::vector<GlyphPosition> positions;
        float width;
    };

    struct LineLayout {
        base::vector<LayoutRun> runs;
    };

    struct RasterResult {
        Bitmap bitmap;
        float glyph_width;
        float glyph_height;
        float descent;
    };

    class TextSystem {
    public:
        virtual ~TextSystem() = default;

        virtual LineLayout layoutLine(base::string_view str) = 0;
        /// warning: alpha only
        virtual RasterResult rasterizeGlyph(GlyphId id) = 0;
    };

}  // namespace spargel::ui
