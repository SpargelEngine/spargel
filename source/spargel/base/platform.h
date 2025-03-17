#pragma once

#include <spargel/base/string.h>

namespace spargel::base {

    /*
     * platform utilities
     */

    /*
     * dynamic library
     */

    struct dynamic_library_handle;

    dynamic_library_handle* open_dynamic_library(const char* filename);

    void close_dynamic_library(dynamic_library_handle* handle);

    void* get_proc_address(dynamic_library_handle* handle, const char* name);

    /**
     * @brief get the absolute path of the executable file associated to
     * the currently process
     *
     * When the actual path string is longer than buf_size, the content of
     * the buffer is undefined.
     *
     * @param buf the buffer to which the path string will be written to
     * @param buf_size the size of the buffer
     * @return the length of the path string; zero if the path cannot be got
     */
    usize _get_executable_path(char* buf, usize buf_size);

    string get_executable_path();

}  // namespace spargel::base
