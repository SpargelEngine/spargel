#pragma once

#include <spargel/base/platform.h>

// Emscripten
#include <emscripten.h>
#include <emscripten/console.h>

namespace spargel::base {

    void emscriptenConsoleLog(const char* msg);

    void emscriptenConsoleDebug(const char* msg);

    void emscriptenConsoleInfo(const char* msg);

    void emscriptenConsoleWarn(const char* msg);

    void emscriptenConsoleError(const char* msg);

}  // namespace spargel::base
