#include <spargel/base/logging.h>
#include <spargel/base/panic.h>
#include <spargel/ui/text_linux.h>
#include <spargel/ui/window.h>

namespace spargel::ui {

    TextSystemLinux::TextSystemLinux() {
        auto err = FT_Init_FreeType(&_ft_library);
        if (err) {
            spargel_log_fatal("cannot initialize FreeType library");
            spargel_panic_here();
        }

        // FIXME
        const char* font_path = "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf";
        err = FT_New_Face(_ft_library, font_path, 0, &_ft_face);

        if (err == FT_Err_Unknown_File_Format) {
            spargel_log_info("unknown font file format: \"%s\"", font_path);
            spargel_panic_here();
        } else if (err) {
            spargel_log_info("cannot load font file: \"%s\"", font_path);
            spargel_panic_here();
        }

        spargel_log_debug("font file: \"%s\"", font_path);
        spargel_log_debug("  num_glyphs: %ld", _ft_face->num_glyphs);
        spargel_log_debug("  face_flags: 0x%04lx", _ft_face->face_flags);
        spargel_log_debug("  units_per_EM: %d", _ft_face->units_per_EM);
        spargel_log_debug("  num_fixed_sizes: %d", _ft_face->num_fixed_sizes);

        err = FT_Set_Pixel_Sizes(_ft_face, 0, 16);
        if (err) {
            spargel_log_fatal("cannot set pixel sizes");
            spargel_panic_here();
        }
    }

    TextSystemLinux::~TextSystemLinux() {}

    // TODO
    LineLayout TextSystemLinux::layoutLine(base::string_view str) {
        LayoutRun run;
        run.width = 0;

        float pos = 0;
        for (usize i = 0; i < str.length(); i++) {
            auto glyph_index = FT_Get_Char_Index(_ft_face, str.data()[i]);
            run.glyphs.push(glyph_index);
            GlyphPosition glyph_pos{.x = pos, .y = 0};
            run.positions.push(glyph_pos);
        }

        run.width = pos;

        LineLayout layout;
        layout.runs.push(base::move(run));

        return layout;
    }

    RasterResult TextSystemLinux::rasterizeGlyph(GlyphId id) {
        auto err = FT_Load_Glyph(_ft_face, id, FT_LOAD_DEFAULT);
        if (err) {
            spargel_log_fatal("cannot load glyph %d", id);
            spargel_panic_here();
        }

        FT_GlyphSlot slot = _ft_face->glyph;

        err = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
        if (err) {
            spargel_log_fatal("cannot render glyph %d", id);
            spargel_panic_here();
        }

        u32 width = slot->bitmap.width, height = slot->bitmap.rows;

        // FIXME
        Bitmap bitmap;
        bitmap.width = width;
        bitmap.height = height;
        bitmap.data.reserve(width * height);
        bitmap.data.set_count(width * height);
        memcpy(bitmap.data.data(), slot->bitmap.buffer, width * height);

        // FIXME
        RasterResult result;
        result.bitmap = base::move(bitmap);
        result.glyph_width = width;
        result.glyph_height = height;
        result.descent = 0;

        return result;
    }

}  // namespace spargel::ui
