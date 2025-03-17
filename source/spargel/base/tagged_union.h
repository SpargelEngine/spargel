#pragma once

#include <spargel/base/meta.h>
#include <spargel/base/panic.h>
#include <spargel/base/sum_type.h>
#include <spargel/base/type_list.h>

namespace spargel::base {

    namespace _tagged_union {

        struct Sentinel;

        template <auto t, typename T = Sentinel>
        struct Case {};

        template <typename...>
        struct CollectTypes;

        template <>
        struct CollectTypes<> {
            using Type = TypeList<>;
        };

        template <auto t, typename C, typename... Cs>
            requires (!is_same<C, Sentinel>)
        struct CollectTypes<Case<t, C>, Cs...> {
            using Type = Cons<C, typename CollectTypes<Cs...>::Type>;
        };

        template <usize i, auto t, typename... Cs>
        struct GetIndex;

        template <usize i, auto t, typename C, typename... Cs>
        struct GetIndex<i, t, Case<t, C>, Cs...> {
            static constexpr usize value = i;
        };

        template <usize i, auto t, auto s, typename C, typename... Cs>
        struct GetIndex<i, t, Case<s, C>, Cs...> {
            static constexpr usize value = GetIndex<i + 1, t, Cs...>::value;
        };

        template <usize i,typename... Cs>
        struct IndexToTag;

        template <auto t, typename T, typename... Cs>
        struct IndexToTag<0, Case<t, T>, Cs...> {
            static constexpr auto value = t;
        };

        template <usize i, auto t, typename T, typename... Cs>
        struct IndexToTag<i, Case<t, T>, Cs...> {
            static constexpr auto value = IndexToTag<i - 1, Cs...>::value;
        };

        template <usize>
        struct Index {};

        template <usize N, usize i = 0, typename F>
            requires(i < N)
        decltype(auto) visitByIndex(usize id, F&& f) {
            if (i == id) {
                return f(Index<i>{});
            }
            if constexpr (i + 1 == N) {
                spargel_panic_here();
            } else {
                return visitByIndex<N, i + 1>(id, base::forward<F>(f));
            }
        }

        template <typename... Ts>
        struct MatchHelper : Ts... {
            using Ts::operator()...;
        };

        template <typename... Ts>
        MatchHelper(Ts...) -> MatchHelper<Ts...>;

        template <typename... Cases>
        class TaggedUnion {
            using Types = CollectTypes<Cases...>::Type;
            using Storage = Apply<SumType, Types>;
            static constexpr usize Count = sizeof...(Cases);

        public:
            template <auto t, typename... Args>
            static TaggedUnion make(Args&&... args) {
                return TaggedUnion(Index<GetIndex<0, t, Cases...>::value>{}, base::forward<Args>(args)...);
            }

            auto tag() {
                return visitByIndex<Count>(_storage.getIndex(), []<usize i>(Index<i>) {
                    return IndexToTag<i, Cases...>::value;
                });
            }

            template <typename... F>
            decltype(auto) match(F&&... f) {
                auto helper = MatchHelper{f...};
                return visitByIndex<Count>(_storage.getIndex(), [&helper, this]<usize i>(Index<i>) {
                    return helper(Case<IndexToTag<i, Cases...>::value>{}, _storage.template getValue<i>());
                });
            }

        private:
            template <usize i, typename... Args>
            TaggedUnion(Index<i>, Args&&... args) : _storage(Storage::template make<i>(base::forward<Args>(args)...)) {}

            Storage _storage;
        };

    }

    using _tagged_union::TaggedUnion;
    using _tagged_union::Case;

}  // namespace spargel::base
