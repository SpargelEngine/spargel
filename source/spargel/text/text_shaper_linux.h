#pragma once

#include "spargel/text/text_shaper.h"

// HarfBuzz
#include <harfbuzz/hb.h>

namespace spargel::text {

    class TextShaperLinux : public TextShaper {
    public:
        ShapedLine shapeLine(const StyledText& text) override;
    };

}  // namespace spargel::text
