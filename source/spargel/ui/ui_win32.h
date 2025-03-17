#pragma once

#include <spargel/base/vector.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>
#include <spargel/ui/ui_dummy.h>

// Windows
#include <windows.h>

namespace spargel::ui {

    class WindowWin32;

    class PlatformWin32 : public Platform {
        friend WindowWin32;

    public:
        PlatformWin32(HINSTANCE hInstance) : Platform(PlatformKind::win32), _hInstance(hInstance) {}

        void startLoop() override;

        base::unique_ptr<Window> makeWindow(u32 width, u32 height) override;
        base::unique_ptr<TextSystem> createTextSystem() override {
            return base::make_unique<TextSystemDummy>();
        }

    private:
        HINSTANCE _hInstance;

        base::vector<WindowWin32*> _windows;

        void _run_render_callbacks();
    };

    class WindowWin32 : public Window {
        friend PlatformWin32;

    public:
        WindowWin32(PlatformWin32* platform, HWND hwnd);
        ~WindowWin32() override;

        void setTitle(char const* title) override;

        void setAnimating(bool animating) override {}

        void requestRedraw() override {}

        WindowHandle getHandle() override;

    private:
        PlatformWin32* _platform;
        HWND _hwnd;
    };

    base::unique_ptr<Platform> makePlatformWin32();

}  // namespace spargel::ui
