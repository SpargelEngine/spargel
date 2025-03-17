#pragma once

#include <spargel/ui/text_system.h>

// FreeType 2
#include <ft2build.h>
#include FT_FREETYPE_H

namespace spargel::ui {

    class TextSystemLinux final : public TextSystem {
    public:
        TextSystemLinux();
        ~TextSystemLinux();

        LineLayout layoutLine(base::string_view str) override;
        RasterResult rasterizeGlyph(GlyphId id) override;

    private:
        FT_Library _ft_library;
        FT_Face _ft_face;
    };

}  // namespace spargel::ui
