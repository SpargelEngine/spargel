#pragma once

#include <spargel/base/panic.h>
#include <spargel/config.h>

#if SPARGEL_ENABLE_ASSERT
#define spargel_assert(cond) ((cond) ? (void)(0) : spargel_panic_here())
#else
#define spargel_assert(cond)
#endif
