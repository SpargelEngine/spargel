#pragma once

#include <spargel/base/meta.h>

namespace spargel::base {

    template <typename S, typename T>
    concept ConvertibleTo = base::is_convertible<S, T>;

    template <typename S, typename T>
    concept SameAs = base::is_same<S, T>;

}  // namespace spargel::base
