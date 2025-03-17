#include <spargel/base/platform_emscripten.h>

// libc
#include <string.h>

namespace spargel::base {

    void emscriptenConsoleLog(const char* msg) {
        EM_ASM({ console.log(UTF8ToString($0)); }, msg);
    }

    void emscriptenConsoleDebug(const char* msg) {
        EM_ASM({ console.debug(UTF8ToString($0)); }, msg);
    }

    void emscriptenConsoleInfo(const char* msg) {
        EM_ASM({ console.info(UTF8ToString($0)); }, msg);
    }

    void emscriptenConsoleWarn(const char* msg) {
        EM_ASM({ console.warn(UTF8ToString($0)); }, msg);
    }

    void emscriptenConsoleError(const char* msg) {
        EM_ASM({ console.error(UTF8ToString($0)); }, msg);
    }

    usize _get_executable_path(char* buf, usize buf_size) {
        char const todo[] = "./todo.js";
        strcpy(buf, todo);
        return strlen(todo);
    }

    // FIXME
    void PrintBacktrace() {
        EM_ASM({ console.trace(); });
    }

}  // namespace spargel::base
