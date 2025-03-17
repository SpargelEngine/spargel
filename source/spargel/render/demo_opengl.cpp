#include <spargel/base/logging.h>
#include <spargel/config.h>
#include <spargel/resource/directory.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>

using namespace spargel;

// libc
#include <stdlib.h>

// GLAD
#include <glad/gl.h>

#if SPARGEL_IS_LINUX
#include <GL/glx.h>
#elif SPARGEL_IS_WINDOWS
#include <windows.h>
#else
#error unimplemented
#endif

class delegate final : public ui::WindowDelegate {
public:
    void onRender() override {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

#if SPARGEL_IS_LINUX
        glXSwapBuffers(_x_display, _x_window);
#elif SPARGEL_IS_WINDOWS
        wglSwapLayerBuffers(_win32_hdc, WGL_SWAP_MAIN_PLANE);
#endif
    }

    unsigned int program;
    unsigned int vao;

#if SPARGEL_IS_LINUX
    Display* _x_display;
    int _x_window;
#elif SPARGEL_IS_WINDOWS
    HDC _win32_hdc;
#endif
};

int main() {
    auto resource_manager = resource::makeRelativeManager(base::string("resources"));

    auto platform = ui::makePlatform();
    auto window = platform->makeWindow(800, 600);
    delegate d;
    window->setDelegate(&d);
    window->setTitle("Spargel Demo - OpenGL");

    auto handle = window->getHandle();

#if SPARGEL_IS_LINUX
    auto x_window = handle.xcb.window;
    auto x_display = (Display*)handle.xcb.display;
    auto x_visual_info = (XVisualInfo*)handle.xcb.visual_info;

    d._x_display = x_display;
    d._x_window = x_window;

    GLXContext glx_ctx = glXCreateContext(x_display, x_visual_info, nullptr, GL_TRUE);
    if (!glx_ctx) {
        spargel_log_fatal("cannot create GL context");
        spargel_panic_here();
    }

    if (!glXMakeCurrent(x_display, x_window, glx_ctx)) {
        spargel_log_fatal("cannot make GL context current");
        spargel_panic_here();
    }
#elif SPARGEL_IS_WINDOWS
    auto hwnd = (HWND)handle.win32.hwnd;
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,  // Flags
        PFD_TYPE_RGBA,  // The kind of framebuffer. RGBA or palette.
        32,             // Colordepth of the framebuffer.
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        24,  // Number of bits for the depthbuffer
        8,   // Number of bits for the stencilbuffer
        0,   // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0,
        0,
        0};

    HDC win32_hdc = GetDC(hwnd);
    d._win32_hdc = win32_hdc;

    int pixelFormat;
    pixelFormat = ChoosePixelFormat(win32_hdc, &pfd);
    SetPixelFormat(win32_hdc, pixelFormat, &pfd);

    HGLRC wgl_ctx = wglCreateContext(win32_hdc);

    wglMakeCurrent(win32_hdc, wgl_ctx);
#endif

    spargel_log_info("Glad generator version: %s", GLAD_GENERATOR_VERSION);

    gladLoaderLoadGL();

    int success;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto vertexShaderCode = resource_manager->open(resource::ResourceId("demo_opengl.vs"));
    if (!vertexShaderCode.hasValue()) {
        spargel_log_fatal("cannot open vertex shader file");
        spargel_panic_here();
    }
    auto pVertexShaderCode = (GLchar*)vertexShaderCode.value()->mapData();
    auto vertexShaderCodeLength = (GLint)vertexShaderCode.value()->size();
    glShaderSource(vertexShader, 1, &pVertexShaderCode, &vertexShaderCodeLength);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        spargel_log_fatal("vertex shader compile error: %s", infoLog);
        spargel_panic_here();
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragmentShaderCode = resource_manager->open(resource::ResourceId("demo_opengl.fs"));
    if (!fragmentShaderCode.hasValue()) {
        spargel_log_fatal("cannot open fragment shader file");
        spargel_panic_here();
    }
    auto pFragmentShaderCode = (GLchar*)fragmentShaderCode.value()->mapData();
    auto fragmentShaderCodeLength = (GLint)fragmentShaderCode.value()->size();
    glShaderSource(fragmentShader, 1, &pFragmentShaderCode, &fragmentShaderCodeLength);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        spargel_log_fatal("fragment shader compile error: %s", infoLog);
        spargel_panic_here();
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        spargel_log_fatal("shader program link error: %s", infoLog);
        spargel_panic_here();
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    d.program = shaderProgram;

    float vertices[] = {
        // positions         // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    d.vao = vao;

    platform->startLoop();

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);

    gladLoaderUnloadGL();

#if SPARGEL_IS_LINUX
    glXDestroyContext(x_display, glx_ctx);
#elif SPARGEL_IS_WINDOWS
    wglDeleteContext(wgl_ctx);
#endif

    return 0;
}
