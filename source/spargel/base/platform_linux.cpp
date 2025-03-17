/*
 * Android-target build also uses this file.
 */

#include <libunwind-x86_64.h>
#include <spargel/base/platform.h>

/* libc */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// libunwind
#define UNW_LOCAL_ONLY
#include <libunwind.h>

namespace spargel::base {

    usize _get_executable_path(char* buf, usize buf_size) {
        return readlink("/proc/self/exe", buf, buf_size);
    }

#if SPARGEL_IS_LINUX

    void PrintBacktrace() {
        unw_cursor_t cursor;
        unw_context_t ctx;

        unw_getcontext(&ctx);
        unw_init_local(&cursor, &ctx);

        while (unw_step(&cursor) > 0) {
            unw_word_t pc, offset;
            char proc_name[1024];
            unw_get_reg(&cursor, UNW_REG_IP, &pc);

            if (unw_get_proc_name(&cursor, proc_name, sizeof(proc_name), &offset) == 0) {
                printf("  %p: %s + %p\n", (void*)pc, proc_name, (void*)offset);
            } else {
                printf("  %p\n", (void*)pc);
            }
        }
    }

#else  // SPARGEL_IS_LINUX

    void PrintBacktrace() { puts("<unknown backtrace>"); }

#endif  // SPARGEL_IS_LINUX

}  // namespace spargel::base
