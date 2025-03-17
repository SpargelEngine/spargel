#pragma once

#include <spargel/base/types.h>

//
#include <string.h>

namespace spargel::base {

    class string_view {
    public:
        constexpr string_view() = default;
        constexpr string_view(char const* begin, char const* end) : _begin{begin}, _end{end} {}
        template <usize N>
        constexpr string_view(char const (&str)[N]) : string_view(str, str + N - 1) {}

        constexpr char operator[](usize i) const { return _begin[i]; }
        constexpr usize length() const { return _end - _begin; }
        constexpr char const* begin() const { return _begin; }
        constexpr char const* end() const { return _end; }
        constexpr char const* data() const { return _begin; }

        friend bool operator==(string_view const& lhs, string_view const& rhs) {
            if (lhs.length() != rhs.length()) return false;
            return memcmp(lhs._begin, rhs._begin, lhs.length()) == 0;
        }

    private:
        char const* _begin = nullptr;
        char const* _end = nullptr;
    };

}  // namespace spargel::base
