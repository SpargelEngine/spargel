#include <spargel/base/platform.h>

// POSIX
#include <dlfcn.h>

namespace spargel::base {

    struct dynamic_library_handle {};

    dynamic_library_handle* open_dynamic_library(const char* filename) {
        return (dynamic_library_handle*)dlopen(filename, RTLD_NOW | RTLD_LOCAL);
    }

    void close_dynamic_library(dynamic_library_handle* handle) { dlclose((void*)handle); }

    void* get_proc_address(dynamic_library_handle* handle, const char* name) {
        return dlsym((void*)handle, name);
    }

}  // namespace spargel::base
