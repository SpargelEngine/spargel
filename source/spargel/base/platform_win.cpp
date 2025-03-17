#include <spargel/base/platform.h>

/* libc */
#include <stdio.h>

/* Windows */
#include <windows.h>

namespace spargel::base {

    struct dynamic_library_handle {};

    dynamic_library_handle* open_dynamic_library(const char* filename) {
        return (dynamic_library_handle*)LoadLibraryA(filename);
    }

    void close_dynamic_library(dynamic_library_handle* handle) { FreeLibrary((HMODULE)handle); }

    void* get_proc_address(dynamic_library_handle* handle, const char* name) {
        return (void*)GetProcAddress((HMODULE)handle, name);
    }

    usize _get_executable_path(char* buf, usize buf_size) {
        return GetModuleFileNameA(NULL, buf, buf_size);
    }

    void PrintBacktrace() { printf("<unknown backtrace>\n"); }

}  // namespace spargel::base
