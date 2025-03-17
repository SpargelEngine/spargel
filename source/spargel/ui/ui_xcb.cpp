#include <spargel/base/logging.h>
#include <spargel/ui/ui_xcb.h>

/* for clock_gettime */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/* libc */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace spargel::ui {

    base::unique_ptr<Platform> makePlatformXcb() { return base::make_unique<PlatformXcb>(); }

    PlatformXcb::PlatformXcb() : Platform(PlatformKind::xcb) {
        /*
         * Open the connection to the X server.
         * Use the DISPLAY environment variable as the default display name.
         */
        _display = XOpenDisplay(NULL);
        spargel_log_debug("X display opened");

        _connection = XGetXCBConnection(_display);
        spargel_log_debug("XCB connection established");

        /* Get the first screen */
        _screen = xcb_setup_roots_iterator(xcb_get_setup(_connection)).data;

        spargel_log_info("Information of XCB screen %d:", _screen->root);
        spargel_log_info("  width:\t%d", _screen->width_in_pixels);
        spargel_log_info("  height:\t%d", _screen->height_in_pixels);
        spargel_log_info("  white pixel:\t%08x", _screen->white_pixel);
        spargel_log_info("  black pixel:\t%08x", _screen->black_pixel);

#if SPARGEL_ENABLE_OPENGL
        _visual_info = nullptr;

        int glx_major, glx_minor;
        glXQueryVersion(_display, &glx_major, &glx_minor);
        spargel_log_info("GLX version: %d.%d", glx_major, glx_minor);
#endif

        xcb_intern_atom_cookie_t cookie;
        xcb_intern_atom_reply_t* reply;

        cookie = _intern_atom_cookie(1, "WM_PROTOCOLS");
        reply = _intern_atom_reply(cookie);
        _atom_wm_protocols = reply->atom;
        free(reply);

        cookie = _intern_atom_cookie(0, "WM_DELETE_WINDOW");
        reply = _intern_atom_reply(cookie);
        _atom_wm_delete_window = reply->atom;
        free(reply);
    }

    PlatformXcb::~PlatformXcb() {
#if SPARGEL_ENABLE_OPENGL
        XFree(_visual_info);
#endif

        // should not do this
        // xcb_disconnect(_connection);

        XCloseDisplay(_display);
    }

    const float FPS = 60;
    const unsigned int SECOND_NS = 1000000000U;
    const unsigned int FRAME_DELTA_NS = (unsigned int)(SECOND_NS / FPS);

    static bool in_delta(struct timespec* t1, struct timespec* t2, unsigned int delta) {
        if (t1->tv_sec == t2->tv_sec) {
            return t2->tv_nsec < t1->tv_nsec + delta;
        } else if (t1->tv_sec == t2->tv_sec - 1) {
            return t2->tv_nsec + SECOND_NS < t1->tv_nsec + delta;
        } else {
            return false;
        }
    }

    void PlatformXcb::startLoop() {
        xcb_generic_event_t* event;
        struct timespec t1, t2, duration = {.tv_sec = 0, .tv_nsec = 0};
        while (true) {
            bool should_stop = true;
            for (auto& window : _windows) {
                if (!window->_closed) {
                    should_stop = false;
                    break;
                }
            }
            if (should_stop) break;

            event = xcb_poll_for_event(_connection);
            if (!event) {
                clock_gettime(CLOCK_MONOTONIC, &t1);

                _run_render_callbacks();
                xcb_flush(_connection);

                /*
                 * wait for the next frame
                 * Normally the sleeping only occurs once each frame.
                 */
                while (true) {
                    clock_gettime(CLOCK_MONOTONIC, &t2);
                    if (in_delta(&t1, &t2, FRAME_DELTA_NS)) {
                        duration.tv_nsec = FRAME_DELTA_NS;
                        clock_nanosleep(CLOCK_MONOTONIC, 0, &duration, NULL);
                    } else {
                        break;
                    }
                }

                continue;
            }

            switch (event->response_type & 0x7f) {
            case XCB_CLIENT_MESSAGE: {
                auto* client_message_event = (xcb_client_message_event_t*)event;
                if (client_message_event->data.data32[0] == _atom_wm_delete_window) {
                    for (auto& window : _windows) {
                        if (window->_id == client_message_event->window) {
                            window->_closed = true;
                            window->getDelegate()->onCloseRequested();
                            window->getDelegate()->onClosed();
                            break;
                        }
                    }
                }
            } break;
            case XCB_EXPOSE: {
                _run_render_callbacks();
                xcb_flush(_connection);
            } break;
            case XCB_KEY_PRESS: {
                // TODO
            } break;
            default:
                break;
            }

            free(event);
        }
    }

    void PlatformXcb::_run_render_callbacks() {
        for (auto& window : _windows) {
            auto delegate = window->getDelegate();
            if (!delegate) {
                spargel_log_fatal("window delegate not set");
                spargel_panic_here();
            }
            delegate->onRender();
        }
    }

    xcb_intern_atom_cookie_t PlatformXcb::_intern_atom_cookie(u8 only_if_exists, const char* name) {
        return xcb_intern_atom(_connection, only_if_exists, strlen(name), name);
    }

    xcb_intern_atom_reply_t* PlatformXcb::_intern_atom_reply(xcb_intern_atom_cookie_t cookie) {
        return xcb_intern_atom_reply(_connection, cookie, nullptr);
    }

    base::unique_ptr<Window> PlatformXcb::makeWindow(u32 width, u32 height) {
        xcb_window_t id = xcb_generate_id(_connection);

#if SPARGEL_ENABLE_OPENGL
        if (!_visual_info) {
            static int attribs[] = {GLX_RENDER_TYPE,
                                    GLX_RGBA_BIT,
                                    GLX_RED_SIZE,
                                    8,
                                    GLX_GREEN_SIZE,
                                    8,
                                    GLX_BLUE_SIZE,
                                    8,
                                    GLX_ALPHA_SIZE,
                                    8,
                                    GLX_DEPTH_SIZE,
                                    24,
                                    GLX_STENCIL_SIZE,
                                    8,
                                    GLX_DOUBLEBUFFER,
                                    True,
                                    None};

            _visual_info = glXChooseVisual(_display, 0, attribs);
            if (_visual_info) {
                spargel_log_info("selected visual 0x%lx for GLX", _visual_info->visualid);
            } else {
                spargel_log_fatal("cannot find appropriate visual for GLX");
                spargel_panic_here();
            }
        }

        xcb_visualid_t visual_id = _visual_info->visualid;
        uint8_t depth = _visual_info->depth;

#else
        xcb_visualid_t visual_id = _screen->root_visual;
        uint8_t depth = XCB_COPY_FROM_PARENT;
#endif

        u32 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        u32 values[2] = {_screen->black_pixel, XCB_EVENT_MASK_EXPOSURE};

        spargel_log_debug("creating X window %d", id);

        xcb_create_window(_connection, depth,            /* depth*/
                          id, _screen->root,             /* parent window */
                          0, 0,                          /* x, y */
                          width, height,                 /* width, height */
                          0,                             /* border width */
                          XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class */
                          visual_id,                     /* visual */
                          mask, values);

        xcb_change_property(_connection, XCB_PROP_MODE_REPLACE, id, _atom_wm_protocols,
                            XCB_ATOM_ATOM, XCB_ATOM_VISUALID, 1, &_atom_wm_delete_window);

        xcb_map_window(_connection, id);
        xcb_flush(_connection);

        return base::make_unique<WindowXcb>(this, id);
    }

    WindowXcb::WindowXcb(PlatformXcb* platform, xcb_window_t id)
        : _platform(platform), _id(id), _closed(false) {
        platform->_windows.push(this);
    }

    WindowXcb::~WindowXcb() {
        spargel_log_debug("X window %d is closing", _id);
        xcb_destroy_window(_platform->_connection, _id);
    }

    void WindowXcb::setTitle(char const* title) {
        spargel_log_debug("setting the title of X window %d to \"%s\"", _id, title);
        xcb_change_property(_platform->_connection, XCB_PROP_MODE_REPLACE, _id, XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING, 8, strlen(title), title);
    }

    WindowHandle WindowXcb::getHandle() {
        WindowHandle handle{};

        handle.xcb.connection = _platform->_connection;
        handle.xcb.window = _id;

        handle.xcb.display = _platform->_display;
#if SPARGEL_ENABLE_OPENGL
        handle.xcb.visual_info = _platform->_visual_info;
#endif

        return handle;
    }

}  // namespace spargel::ui
