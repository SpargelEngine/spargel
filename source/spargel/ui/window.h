#pragma once

#include <spargel/ui/event.h>

namespace spargel::ui {

    /// the native handle of a window
    struct WindowHandle {
        union {
            struct {
                void* window;
            } android;
            struct {
                void* layer;
            } apple;
            struct {
                void* display;
                void* surface;
            } wayland;
            struct {
                void* hinstance;
                void* hwnd;
            } win32;
            struct {
                void* connection;
                int window;

                // Xlib things, for GLX
                void* display;
                void* visual_info;
            } xcb;
        };
    };

    class WindowDelegate {
    public:
        virtual ~WindowDelegate() = default;

        /// @brief the window is requested to draw the contents
        virtual void onRender() {}

        /// @brief the window is requested to close
        virtual void onCloseRequested() {}

        /// @brief the window is closed
        virtual void onClosed() {}

        /// @brief a keyboard event is received
        virtual void onKeyboard(KeyboardEvent& e) {}

        virtual void onMouseDown(float x, float y) {}

        /// User has moved the mouse with left button pressed.
        virtual void onMouseDragged(float dx, float dy) {}
    };

    // The coordinate system is TLO (top-left origin).
    //
    class Window {
    public:
        virtual ~Window() = default;

        void setDelegate(WindowDelegate* delegate) { _delegate = delegate; }
        WindowDelegate* getDelegate() { return _delegate; }

        virtual void setTitle(char const* title) = 0;

        virtual void setAnimating(bool animating) = 0;

        virtual void requestRedraw() = 0;

        // todo: improve
        virtual WindowHandle getHandle() = 0;

    private:
        WindowDelegate* _delegate = nullptr;
    };


}  // namespace spargel::ui
