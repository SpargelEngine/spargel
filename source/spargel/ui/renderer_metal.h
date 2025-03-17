#pragma once

#include <spargel/ui/renderer.h>

namespace spargel::ui {

    class RendererMetal final : public Renderer {};

    /// A `LayerMetal` is a Metal texture.
    class LayerMetal final : public Layer {
    public:
    private:
        id<MTLTexture> _texture;
    };

}  // namespace spargel::ui
