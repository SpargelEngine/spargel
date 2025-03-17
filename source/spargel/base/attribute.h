#pragma once

#include <spargel/base/compiler.h>

// "inline" seems to be needed

#if defined(SPARGEL_IS_CLANG)
#define SPARGEL_ALWAYS_INLINE [[clang::always_inline]]
#elif defined(SPARGEL_IS_GCC)
#define SPARGEL_ALWAYS_INLINE [[gnu::always_inline]]
#elif defined(SPARGEL_IS_MSVC)
#define SPARGEL_ALWAYS_INLINE __forceinline
#else
#define SPARGEL_ALWAYS_INLINE
#endif
