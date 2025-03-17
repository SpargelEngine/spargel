#pragma once

#include <spargel/base/attribute.h>

namespace spargel::math {

    /// 4x4 matrix.
    ///
    /// The storage is column-major.
    ///
    template <typename T>
    struct Matrix4x4 {
        // column-major
        // T entries[4][4];
        T entries[16];

        Matrix4x4() = default;

        // clang-format off
        SPARGEL_ALWAYS_INLINE Matrix4x4(T a11, T a21, T a31, T a41,
                                        T a12, T a22, T a32, T a42,
                                        T a13, T a23, T a33, T a43,
                                        T a14, T a24, T a34, T a44)
            // : entries{{a11, a21, a31, a41},
            //           {a12, a22, a32, a42},
            //           {a13, a23, a33, a43},
            //           {a14, a24, a34, a44}} {}
            : entries{a11, a21, a31, a41,
                      a12, a22, a32, a42,
                      a13, a23, a33, a43,
                      a14, a24, a34, a44} {}
        // clang-format on
    };

    using Matrix4x4f = Matrix4x4<float>;

}  // namespace spargel::math
