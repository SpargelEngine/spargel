#pragma once

/*
 * Different compilers have different definition for std::initializer_list,
 * so we just use the standard library.
 */
#include <initializer_list>

namespace spargel::base {

    using std::initializer_list;

}
