#pragma once

#include <spargel/base/type_list.h>

namespace spargel::base {
    namespace _tuple {
        template <usize... Is>
        struct IntegerSequence;

        template <typename T, usize I>
        struct Append;
        template <usize I, usize... Js>
        struct Append<IntegerSequence<Js...>, I> {
            using Type = IntegerSequence<Js..., I>;
        };
        template <usize N>
        struct MakeSequence {
            using Type = Append<typename MakeSequence<N - 1>::Type, N - 1>::Type;
        };
        template <>
        struct MakeSequence<0> {
            using Type = IntegerSequence<>;
        };

        // L is a TypeList
        template <usize i, typename L>
        struct TupleItem {
            using Type = Get<L, i>;
            Type data;
        };
        // L is a TypeList
        template <typename L, typename I>
        struct TupleStorage;
        template <typename L, usize... Is>
        struct TupleStorage<L, IntegerSequence<Is...>> : TupleItem<Is, L>... {
            template <usize i>
            auto& get() {
                return TupleItem<i, L>::data;
            }
        };
        template <typename... Ts>
        class Tuple {
        public:
            template <usize i>
            auto& get() {
                return _storage.template get<i>();
            }
        private:
            TupleStorage<TypeList<Ts...>, typename MakeSequence<sizeof...(Ts)>::Type> _storage; 
        };
    }
    using _tuple::Tuple;
}
