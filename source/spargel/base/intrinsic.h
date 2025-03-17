#pragma once

#include <spargel/base/assert.h>
#include <spargel/base/compiler.h>
#include <spargel/base/types.h>

namespace spargel::base {

    inline u8 GetMostSignificantBit(u64 x) {
        spargel_assert(x > 0);

#if spargel_has_builtin(__builtin_clzll)
        // __builtin_clz:
        //   Returns the number of leading 0-bits in x, starting at the most
        //   significant bit position. If x is 0, the result is undefined.
        return 63 - __builtin_clzll(x);
#endif
    }

}  // namespace spargel::base
