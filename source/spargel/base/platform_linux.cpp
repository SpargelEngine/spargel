#include <spargel/base/platform.h>

/* libc */
#include <stdio.h>
#include <unistd.h>

namespace spargel::base {

    usize _get_executable_path(char* buf, usize buf_size) {
        return readlink("/proc/self/exe", buf, buf_size);
    }

    void PrintBacktrace() { printf("<unknown backtrace>\n"); }

}  // namespace spargel::base
