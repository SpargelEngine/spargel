#pragma once

#include <spargel/base/unique_ptr.h>

namespace spargel::ui {

    class Window;
    class TextSystem;

    enum class PlatformKind {
        android,
        appkit,
        dummy,
        uikit,
        wayland,
        win32,
        xcb,
    };

    class Platform {
    public:
        virtual ~Platform() = default;

        PlatformKind getKind() const { return _kind; }

        virtual void startLoop() = 0;

        virtual base::unique_ptr<Window> makeWindow(u32 width, u32 height) = 0;

        virtual base::unique_ptr<TextSystem> createTextSystem() = 0;

    protected:
        explicit Platform(PlatformKind kind) : _kind{kind} {}

    private:
        PlatformKind _kind;
    };

    base::unique_ptr<Platform> makePlatform();

}  // namespace spargel::ui
