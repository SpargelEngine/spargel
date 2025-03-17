#pragma once

#include <spargel/base/vector.h>
#include <spargel/config.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/ui_dummy.h>
#include <spargel/ui/window.h>

/* X11 */
#include <X11/Xlib-xcb.h>
#include <X11/Xlib.h>
#include <xcb/xcb.h>

#if SPARGEL_ENABLE_OPENGL
/* GLX */
#include <GL/glx.h>
#endif

namespace spargel::ui {

    class WindowXcb;

    class PlatformXcb : public Platform {
        friend WindowXcb;

    public:
        PlatformXcb();
        ~PlatformXcb() override;

        void startLoop() override;

        base::unique_ptr<Window> makeWindow(u32 width, u32 height) override;

        base::unique_ptr<TextSystem> createTextSystem() override {
            return base::make_unique<TextSystemDummy>();
        }

    private:
        Display* _display;

        xcb_connection_t* _connection;
        xcb_screen_t* _screen;

#if SPARGEL_ENABLE_OPENGL
        XVisualInfo* _visual_info;
#endif

        base::vector<WindowXcb*> _windows;

        void _run_render_callbacks();

        xcb_atom_t _atom_wm_protocols;
        xcb_atom_t _atom_wm_delete_window;

        xcb_intern_atom_cookie_t _intern_atom_cookie(u8 only_if_exists, const char* name);
        xcb_intern_atom_reply_t* _intern_atom_reply(xcb_intern_atom_cookie_t cookie);
    };

    base::unique_ptr<Platform> makePlatformXcb();

    class WindowXcb : public Window {
        friend PlatformXcb;

    public:
        WindowXcb(PlatformXcb* platform, xcb_window_t id);
        ~WindowXcb() override;

        void setTitle(char const* title) override;

        void setAnimating(bool animating) override {}

        void requestRedraw() override {}

        WindowHandle getHandle() override;

    private:
        PlatformXcb* _platform;
        xcb_window_t _id;
        bool _closed;
    };

}  // namespace spargel::ui
