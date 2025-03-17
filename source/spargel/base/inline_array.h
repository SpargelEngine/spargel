#pragma once

#include <spargel/base/check.h>
#include <spargel/base/types.h>

namespace spargel::base {

    /// A wrapper of the builtin array type `T[N]`.
    ///
    template <typename T, usize size>
    struct InlineArray {
        T& operator[](usize i) {
            spargel_check(i < size);
            return _array[i];
        }
        T const& operator[](usize i) const {
            spargel_check(i < size);
            return _array[i];
        }

        usize count() const { return size; }

        T _array[size];
    };

}  // namespace spargel::base
