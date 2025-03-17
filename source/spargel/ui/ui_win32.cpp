#include <spargel/base/logging.h>
#include <spargel/ui/ui_win32.h>

namespace spargel::ui {

    static const char CLASS_NAME[] = "Spargel Engine Window Class";

    static LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }

    void PlatformWin32::startLoop() {
        MSG msg = {};

        while (true) {
            while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return;
                } else {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
            }

            _run_render_callbacks();
        }
    }

    void PlatformWin32::_run_render_callbacks() {
        for (auto& window : _windows) {
            auto delegate = window->getDelegate();
            if (!delegate) {
                spargel_log_fatal("window delegate not set");
                spargel_panic_here();
            }
            delegate->onRender();
        }
    }

    base::unique_ptr<Window> PlatformWin32::makeWindow(u32 width, u32 height) {
        WNDCLASS wc = {};

        wc.lpfnWndProc = window_proc;
        wc.hInstance = _hInstance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClassA(&wc);

        spargel_log_debug("creating win32 window");

        HWND hwnd = CreateWindowExA(0,                    // optional window styles
                                    CLASS_NAME,           // window class
                                    "Spargel Engine",     // window text
                                    WS_OVERLAPPEDWINDOW,  // window style

                                    // size and position
                                    CW_USEDEFAULT, CW_USEDEFAULT, (int)width, (int)height,

                                    NULL,        // parent window
                                    NULL,        // menu
                                    _hInstance,  // instance handle
                                    NULL         // additional application data
        );

        if (hwnd == NULL) {
            spargel_log_fatal("CreateWindowEx failed");
            spargel_panic_here();
        }

        ShowWindow(hwnd, SW_SHOWNORMAL);

        return base::make_unique<WindowWin32>(this, hwnd);
    }

    WindowWin32::WindowWin32(PlatformWin32* platform, HWND hwnd)
        : _platform(platform), _hwnd(hwnd) {
        platform->_windows.push(this);
    }

    WindowWin32::~WindowWin32() {
        spargel_log_debug("destroying win32 window");
        DestroyWindow(_hwnd);
    }

    void WindowWin32::setTitle(char const* title) {
        spargel_log_debug("setting win32 window title to \"%s\"", title);
        SetWindowTextA(_hwnd, title);
    }

    WindowHandle WindowWin32::getHandle() {
        WindowHandle handle{};
        handle.win32.hinstance = _platform->_hInstance;
        handle.win32.hwnd = _hwnd;
        return handle;
    }

    base::unique_ptr<Platform> makePlatformWin32() {
        HINSTANCE hInstance = (HINSTANCE)GetModuleHandleA(NULL);
        return base::make_unique<PlatformWin32>(hInstance);
    }

}  // namespace spargel::ui
