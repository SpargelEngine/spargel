#pragma once

#include <spargel/base/attribute.h>
#include <spargel/base/meta.h>
#include <spargel/base/types.h>

namespace spargel::base {

    /*
     * An instance of Constructor<T(Args...)> can be used as the constructor of T with the
     * corresponding argument types
     */
    template <typename Signature>
    struct Constructor;

    template <typename T, typename... Args>
    struct Constructor<T(Args...)> {
        T operator()(Args&&... args) const { return T(base::forward<Args>(args)...); }
    };

    // old design
    namespace __curry {

        template <typename F, typename T>
        struct Curried {
            F f;
            T t;

            // SPARGEL_ALWAYS_INLINE
            constexpr Curried(F&& f, T&& t) : f(f), t(t) {}

            template <typename... Args>
            // SPARGEL_ALWAYS_INLINE
            constexpr auto operator()(Args&&... args) {
                return f(base::forward<T>(t), base::forward<Args>(args)...);
            }
        };

        /*
         *  bind a value to the first argument of f and generate a new function with fewer arguments
         */
        template <typename F, typename T, typename... Args>
        // SPARGEL_ALWAYS_INLINE
        constexpr Curried<F, T> curry(F&& f, T&& t) {
            return Curried<F, T>(base::forward<F>(f), base::forward<T>(t));
        }

        // TODO: curryN(F&& f, BoundArgs... bound_args)

    }  // namespace __curry

    using __curry::curry;

    namespace __test {
        // This also seems to work but is even worse
        template <typename F, typename T>
        constexpr auto curry(F&& f, T&& t) {
            return [&f, &t](auto&&... args) {
                return base::forward<F>(f)(base::forward<T>(t),
                                           base::forward<decltype(args)>(args)...);
            };
        }
    }  // namespace __test

}  // namespace spargel::base
