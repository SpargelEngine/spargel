#pragma once

#include <spargel/base/meta.h>
#include <spargel/base/sum_type.h>

namespace spargel::base {

    namespace _either {

        template <typename L>
        struct Left {
            L value;
        };

        template <typename R>
        struct Right {
            R value;
        };

        template <typename L>
        Left(L const&) -> Left<L>;
        template <typename L>
        Left(L&&) -> Left<L>;

        template <typename R>
        Right(R const&) -> Right<R>;
        template <typename R>
        Right(R&&) -> Right<R>;

        template <typename L, typename R>
        class Either {
            using Type = SumType<L, R>;

        public:
            // Constructors
            Either() = default;

            Either(Left<L> const& l) : Either(LeftTag<true>{}, l.value) {}
            Either(Left<L>&& l) : Either(LeftTag<true>{}, base::move(l.value)) {}

            Either(Right<R> const& r) : Either(LeftTag<false>{}, r.value) {}
            Either(Right<R>&& r) : Either(LeftTag<false>{}, base::move(r.value)) {}

            Either(const Either&) = default;

            template <typename L2, typename R2>
                requires(is_convertible<L2, L> && is_convertible<R2, R>)
            Either(Either<L2, R2>&& other)
                : _value(other.isLeft() ? Type::template make<0>(move(other.left()))
                                        : Type::template make<1>(move(other.right()))) {}

            // Assignment operators
            Either& operator=(const Either&) = default;
            Either& operator=(Either&&) = default;

            bool isLeft() const { return _value.getIndex() == 0; }
            bool isRight() const { return _value.getIndex() == 1; }

            // Value accessors
            L& left() { return _value.template getValue<0>(); }
            const L& left() const { return _value.template getValue<0>(); }

            R& right() { return _value.template getValue<1>(); }
            const R& right() const { return _value.template getValue<1>(); }

            template <typename G, typename D, typename... Args>
            friend Either<G, D> makeLeft(Args&&... args);

            template <typename G, typename D, typename... Args>
            friend Either<G, D> makeRight(Args&&... args);

        private:
            template <bool>
            struct LeftTag {};

            template <typename... Args>
            Either(LeftTag<true>, Args&&... args)
                : _value(Type::template make<0>(forward<Args>(args)...)) {}

            template <typename... Args>
            Either(LeftTag<false>, Args&&... args)
                : _value(Type::template make<1>(forward<Args>(args)...)) {}

            Type _value;
        };

        template <typename L, typename R, typename... Args>
        Either<L, R> makeLeft(Args&&... args) {
            return Either<L, R>(typename Either<L, R>::template LeftTag<true>{},
                                forward<Args>(args)...);
        }

        template <typename L, typename R, typename... Args>
        Either<L, R> makeRight(Args&&... args) {
            return Either<L, R>(typename Either<L, R>::template LeftTag<false>{},
                                forward<Args>(args)...);
        }

    }  // namespace _either

    using _either::Either;
    using _either::makeLeft;
    using _either::makeRight;
    using _either::Left;
    using _either::Right;

}  // namespace spargel::base
