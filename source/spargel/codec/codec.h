#pragma once

#include <spargel/base/attribute.h>
#include <spargel/base/concept.h>
#include <spargel/base/either.h>
#include <spargel/base/functional.h>
#include <spargel/base/hash_map.h>
#include <spargel/base/optional.h>
#include <spargel/base/string.h>
#include <spargel/base/vector.h>

// temp
#include <tuple>

namespace spargel::codec {

    /*
     * generic codec error class
     *
     * Error classes for codec API can be easily built base upon this, since they are
     * required to be constructable from error message.
     */
    class CodecError {
    public:
        CodecError(const base::string& message) : _message(message) {}

        CodecError(const base::string_view& message) : _message(message) {}

        CodecError(const char* message) : _message(message) {}

        const base::string& message() { return _message; }

        friend CodecError operator+(const CodecError& error, const base::string_view& str) {
            return CodecError(error._message + str);
        }

        friend CodecError operator+(const CodecError& error, char ch) {
            return CodecError(error._message + ch);
        }

        friend CodecError operator+(const CodecError& error1, const CodecError& error2) {
            return CodecError(error1._message + error2._message);
        }

    private:
        base::string _message;
    };

    /*
     * Generic Codec (Encode/Decode) API
     */

    // We allow codec backend to change itself during operations, so we do not use "const"
    // qualifier.

    // Error classes for codec API should be directly constructable from messages.
    template <typename E>
    concept ConstructableFromMessage =
        requires(const base::string& s) { E(s); } && requires(const base::string_view& s) { E(s); };

    // encode backend prototype
    template <typename EB /* encode backend type */>
    concept EncodeBackend = requires {
        typename EB::DataType;  /* backend data type */
        typename EB::ErrorType; /* encode error type */
        requires ConstructableFromMessage<typename EB::ErrorType>;
    } && requires(EB& backend) {
        backend.makeNull();
        {
            backend.makeNull()
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, bool b) {
        backend.makeBoolean(b);
        {
            backend.makeBoolean(b)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, u8 n) {
        backend.makeU8(n);
        {
            backend.makeU8(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, i8 n) {
        backend.makeI8(n);
        {
            backend.makeI8(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, u16 n) {
        backend.makeU16(n);
        {
            backend.makeU16(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, i16 n) {
        backend.makeI16(n);
        {
            backend.makeI16(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, u32 n) {
        backend.makeU32(n);
        {
            backend.makeU32(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, i32 n) {
        backend.makeI32(n);
        {
            backend.makeI32(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, u64 n) {
        backend.makeU64(n);
        {
            backend.makeU64(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, i64 n) {
        backend.makeI64(n);
        {
            backend.makeI64(n)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, f32 v) {
        backend.makeF32(v);
        {
            backend.makeF32(v)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, f64 v) {
        backend.makeF64(v);
        {
            backend.makeF64(v)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, const base::string& s) {
        backend.makeString(s);
        {
            backend.makeString(s)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, const base::vector<typename EB::DataType>& array) {
        backend.makeArray(array);
        {
            backend.makeArray(array)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    } && requires(EB& backend, const base::HashMap<base::string, typename EB::DataType>& map) {
        backend.makeMap(map);
        {
            backend.makeMap(map)
        } -> base::ConvertibleTo<base::Either<typename EB::DataType, typename EB::ErrorType>>;
    };

    // decode backend prototype
    template <typename DB /* decode backend type */>
    concept DecodeBackend = requires {
        typename DB::DataType;  /* backend data type */
        typename DB::ErrorType; /* decode error type */
        requires ConstructableFromMessage<typename DB::ErrorType>;
    } && requires(DB& backend, const DB::DataType& data) {
        backend.getNull(data);
        { backend.getNull(data) } -> base::ConvertibleTo<base::Optional<typename DB::ErrorType>>;

        backend.getBoolean(data);
        {
            backend.getBoolean(data)
        } -> base::ConvertibleTo<base::Either<bool, typename DB::ErrorType>>;

        backend.getU8(data);
        { backend.getU8(data) } -> base::ConvertibleTo<base::Either<u8, typename DB::ErrorType>>;
        backend.getI8(data);
        { backend.getI8(data) } -> base::ConvertibleTo<base::Either<i8, typename DB::ErrorType>>;
        backend.getU16(data);
        { backend.getU16(data) } -> base::ConvertibleTo<base::Either<u16, typename DB::ErrorType>>;
        backend.getI16(data);
        { backend.getI16(data) } -> base::ConvertibleTo<base::Either<i16, typename DB::ErrorType>>;
        backend.getU32(data);
        { backend.getU32(data) } -> base::ConvertibleTo<base::Either<u32, typename DB::ErrorType>>;
        backend.getI32(data);
        { backend.getI32(data) } -> base::ConvertibleTo<base::Either<i32, typename DB::ErrorType>>;
        backend.getU64(data);
        { backend.getU64(data) } -> base::ConvertibleTo<base::Either<u64, typename DB::ErrorType>>;
        backend.getI64(data);
        { backend.getI64(data) } -> base::ConvertibleTo<base::Either<i64, typename DB::ErrorType>>;

        backend.getF32(data);
        { backend.getF32(data) } -> base::ConvertibleTo<base::Either<f32, typename DB::ErrorType>>;
        backend.getF64(data);
        { backend.getF64(data) } -> base::ConvertibleTo<base::Either<f64, typename DB::ErrorType>>;

        backend.getString(data);
        {
            backend.getString(data)
        } -> base::ConvertibleTo<base::Either<base::string, typename DB::ErrorType>>;

        backend.getArray(data);
        {
            backend.getArray(data)
        } -> base::ConvertibleTo<
              base::Either<base::vector<typename DB::DataType>, typename DB::ErrorType>>;
    } && requires(DB& backend, const DB::DataType& data, const base::string& key) {
        backend.getMember(data, key);
        {
            backend.getMember(data, key)
        } -> base::ConvertibleTo<
              base::Either<base::Optional<typename DB::DataType>, typename DB::ErrorType>>;
    };

    // dummy encode/decode backend
    //   used for constraint checking
    //   also serves as an example
    namespace {

        struct DummyType {};

        struct EncodeBackendDummy {
            using DataType = DummyType;
            using ErrorType = CodecError;

            base::Either<DummyType, CodecError> makeNull();

            base::Either<DummyType, CodecError> makeBoolean(bool b);

            base::Either<DummyType, CodecError> makeU8(u8 n);
            base::Either<DummyType, CodecError> makeI8(i8 n);
            base::Either<DummyType, CodecError> makeU16(u16 n);
            base::Either<DummyType, CodecError> makeI16(i16 n);
            base::Either<DummyType, CodecError> makeU32(u32 n);
            base::Either<DummyType, CodecError> makeI32(i32 n);
            base::Either<DummyType, CodecError> makeU64(u64 n);
            base::Either<DummyType, CodecError> makeI64(i64 n);

            base::Either<DummyType, CodecError> makeF32(f32 v);
            base::Either<DummyType, CodecError> makeF64(f64 v);

            base::Either<DummyType, CodecError> makeString(const base::string& s);

            base::Either<DummyType, CodecError> makeArray(const base::vector<DummyType>& array);

            base::Either<DummyType, CodecError> makeMap(
                const base::HashMap<base::string, DummyType>& map);
        };
        static_assert(EncodeBackend<EncodeBackendDummy>);

        struct DecodeBackendDummy {
            using DataType = DummyType;
            using ErrorType = CodecError;

            base::Optional<CodecError> getNull(const DummyType& data);

            base::Either<bool, CodecError> getBoolean(const DummyType& data);

            base::Either<u8, CodecError> getU8(const DummyType& data);
            base::Either<i8, CodecError> getI8(const DummyType& data);
            base::Either<u16, CodecError> getU16(const DummyType& data);
            base::Either<i16, CodecError> getI16(const DummyType& data);
            base::Either<u32, CodecError> getU32(const DummyType& data);
            base::Either<i32, CodecError> getI32(const DummyType& data);
            base::Either<u64, CodecError> getU64(const DummyType& data);
            base::Either<i64, CodecError> getI64(const DummyType& data);

            base::Either<u64, CodecError> getF32(const DummyType& data);
            base::Either<i64, CodecError> getF64(const DummyType& data);

            base::Either<base::string, CodecError> getString(const DummyType& data);

            base::Either<base::vector<DummyType>, CodecError> getArray(const DummyType& data);

            base::Either<base::Optional<DummyType>, CodecError> getMember(const DummyType& data,
                                                                          const base::string& key);
        };
        static_assert(DecodeBackend<DecodeBackendDummy>);

    }  // namespace

    // encoder prototype
    template <typename E>
    concept Encoder = requires { typename E::Type; } && requires(EncodeBackendDummy& backend,
                                                                 const E::Type& object) {
        E::template encode<EncodeBackendDummy>(backend, object);
        {
            E::template encode<EncodeBackendDummy>(backend, object)
        } -> base::ConvertibleTo<
              base::Either<EncodeBackendDummy::DataType, EncodeBackendDummy::ErrorType>>;
    };

    // decoder prototype
    template <typename D>
    concept Decoder = requires {
        typename D::Type;
    } && requires(DecodeBackendDummy& backend, const DecodeBackendDummy::DataType& data) {
        D::template decode<DecodeBackendDummy>(backend, data);
        {
            D::template decode<DecodeBackendDummy>(backend, data)
        } -> base::ConvertibleTo<base::Either<typename D::Type, DecodeBackendDummy::ErrorType>>;
    };

    template <typename Codec>
    concept EncoderDecoder = Encoder<Codec> && Decoder<Codec>;

    /*
     * utils for encoding maps
     */

    namespace __encode_map {

        struct EncodeField {
            // the entry will always be encoded to the target map
            template <Decoder E>
            struct Normal {
                base::string key;
                E::Type value;

                Normal(const base::string& key, const E::Type value) : key(key), value(value) {}
                Normal(const base::string_view& key, const E::Type value)
                    : key(key), value(value) {}
            };

            // the entry will be encoded to the taregt map only if it exists
            template <Decoder E>
            struct Optional {
                base::string key;
                base::Optional<typename E::Type> value;

                Optional(const base::string& key, const base::Optional<typename E::Type>& value)
                    : key(key), value(value) {}
                Optional(const base::string_view& key,
                         const base::Optional<typename E::Type>& value)
                    : key(key), value(value) {}
            };
        };

        // head for recursive definition: no entries at all
        template <EncodeBackend EB>
        base::Optional<typename EB::ErrorType> encodeToMap(
            base::HashMap<base::string, typename EB::DataType>& map, EB& backend) {
            return base::nullopt;
        }

        // encode one normal entry
        template <EncodeBackend EB, Encoder E, typename... Entries>
        base::Optional<typename EB::ErrorType> encodeToMap(
            base::HashMap<base::string, typename EB::DataType>& map, EB& backend,
            EncodeField::Normal<E> entry, Entries... entries) {
            auto result = E::template encode<EB>(backend, entry.value);
            if (result.isRight()) return base::makeOptional<typename EB::ErrorType>(result.right());

            map.set(entry.key, result.left());

            return encodeToMap(map, backend, base::forward<Entries>(entries)...);
        }

        // encode one optional entry
        template <EncodeBackend EB, Encoder E, typename... Entries>
        base::Optional<typename EB::ErrorType> encodeToMap(
            base::HashMap<base::string, typename EB::DataType>& map, EB& backend,
            EncodeField::Optional<E> entry, Entries... entries) {
            if (entry.value.hasValue()) {
                auto result = E::template encode<EB>(backend, entry.value.value());
                if (result.isRight())
                    return base::makeOptional<typename EB::ErrorType>(result.right());

                map.set(entry.key, result.left());
            }

            return encodeToMap(map, backend, base::forward<Entries>(entries)...);
        }

        // create map, call encodeToMap to encode all the entries, and return the map
        template <EncodeBackend EB, typename... Encoders, typename... Entries>
        base::Either<typename EB::DataType, typename EB::ErrorType> encodeMap(EB& backend,
                                                                              Entries... entries) {
            using DataType = EB::DataType;
            using ErrorType = EB::ErrorType;

            base::HashMap<base::string, DataType> map(base::default_allocator());  // FIXME
            auto result =
                encodeToMap<Encoders...>(map, backend, base::forward<Entries>(entries)...);
            if (result.hasValue()) return base::makeRight<DataType, ErrorType>(result.value());
            return backend.makeMap(base::move(map));
        }

    }  // namespace __encode_map

    using __encode_map::EncodeField;

    using __encode_map::encodeMap;

    /*
     * utils for decoding maps
     */

    namespace __decode_map {

        struct DecodeField {
            // the entry is required to exist
            template <Decoder D>
            struct Required {
                base::string key;

                Required(const base::string& key) : key(key) {}
                Required(const base::string_view& key) : key(key) {}
            };

            // the entry is optional
            template <Decoder D>
            struct Optional {
                base::string key;

                Optional(const base::string& key) : key(key) {}
                Optional(const base::string_view& key) : key(key) {}
            };

            // the entry is optional; if it does not exist, supply a default value as the decode
            // result
            template <Decoder D>
            struct Default {
                base::string key;
                D::Type default_value;

                Default(const base::string& key, const D::Type& default_value)
                    : key(key), default_value(default_value) {}

                Default(const base::string_view& key, const D::Type& default_value)
                    : key(key), default_value(default_value) {}
            };
        };

        namespace _impl {
            template <typename T>
            struct Uninitialized {
                using Type = T;
                template <typename... Args>
                void init(Args&&... args) {
                    base::construct_at(reinterpret_cast<T*>(&bytes), base::forward<Args>(args)...);
                    initialized = true;
                }
                ~Uninitialized() {
                    if (initialized) base::destruct_at((T*)bytes);
                }
                T& get() { return *reinterpret_cast<T*>(&bytes); }
                T const& get() const { return *reinterpret_cast<T const*>(&bytes); }

                bool initialized = false;
                alignas(alignof(T)) base::Byte bytes[sizeof(T)];
            };
            template <typename...>
            struct List;
            template <typename, usize i>
            struct Get;
            template <typename T, typename... Ts>
            struct Get<List<T, Ts...>, 0> {
                using Type = T;
            };
            template <usize i, typename T, typename... Ts>
            struct Get<List<T, Ts...>, i> {
                using Type = Get<List<Ts...>, i - 1>::Type;
            };
            template <typename T, typename S>
            struct ListCons;
            template <typename T, typename... Ts>
            struct ListCons<T, List<Ts...>> {
                using Type = List<T, Ts...>;
            };
            template <typename...>
            struct TupleType;
            template <>
            struct TupleType<> {
                using Type = List<>;
            };
            template <typename T, typename... Ts>
            struct TupleType<DecodeField::Required<T>, Ts...> {
                using Type = ListCons<Uninitialized<typename T::Type>,
                                      typename TupleType<Ts...>::Type>::Type;
            };
            template <typename T, typename... Ts>
            struct TupleType<DecodeField::Optional<T>, Ts...> {
                using Type = ListCons<Uninitialized<base::Optional<typename T::Type>>,
                                      typename TupleType<Ts...>::Type>::Type;
            };
            template <typename T, typename... Ts>
            struct TupleType<DecodeField::Default<T>, Ts...> {
                using Type = ListCons<Uninitialized<typename T::Type>,
                                      typename TupleType<Ts...>::Type>::Type;
            };
            template <typename T>
            struct ListToTuple;
            template <typename... Ts>
            struct ListToTuple<List<Ts...>> {
                using Type = std::tuple<Ts...>;
            };

            template <typename T>
            struct IsRequired {
                static constexpr bool value = false;
            };
            template <typename T>
            struct IsRequired<DecodeField::Required<T>> {
                static constexpr bool value = true;
            };
            template <typename T>
            struct IsOptional {
                static constexpr bool value = false;
            };
            template <typename T>
            struct IsOptional<DecodeField::Optional<T>> {
                static constexpr bool value = true;
            };
            template <typename T>
            struct IsDefault {
                static constexpr bool value = false;
            };
            template <typename T>
            struct IsDefault<DecodeField::Default<T>> {
                static constexpr bool value = true;
            };

            template <typename T>
            struct FieldDecoderType {};
            template <typename T>
            struct FieldDecoderType<DecodeField::Required<T>> {
                using Type = T;
            };
            template <typename T>
            struct FieldDecoderType<DecodeField::Optional<T>> {
                using Type = T;
            };
            template <typename T>
            struct FieldDecoderType<DecodeField::Default<T>> {
                using Type = T;
            };

            template <usize i, usize N, typename DB, typename Tuple, typename L, typename E,
                      typename I>
                requires(i < N)
            bool process(DB& backend, typename DB::DataType const& data, Tuple& t, E& e,
                         I const& ins) {
                bool success = false;
                using T = typename Get<L, i>::Type;
                auto& out = std::get<i>(t);
                auto const& in = std::get<i>(ins);

                auto result = backend.getMember(data, in.key);
                if (result.isRight()) {
                    e.init(base::move(result.right()));
                } else {
                    auto& optional = result.left();

                    if constexpr (IsRequired<T>::value) {
                        if (optional.hasValue()) {
                            auto decode_result = FieldDecoderType<T>::Type::template decode<DB>(
                                backend, base::move(optional.value()));
                            if (decode_result.isRight()) {
                                e.init(base::move(decode_result.right()));
                            } else {
                                success = true;
                                out.init(base::move(decode_result.left()));
                            }
                        } else {
                            e.init(base::string("required member \"") + in.key + "\" not found");
                        }
                    } else if constexpr (IsOptional<T>::value) {
                        if (optional.hasValue()) {
                            auto decode_result = FieldDecoderType<T>::Type::template decode<DB>(
                                backend, base::move(optional.value()));
                            if (decode_result.isRight()) {
                                e.init(base::move(decode_result.right()));
                            } else {
                                success = true;
                                out.init(
                                    base::makeOptional<typename FieldDecoderType<T>::Type::Type>(
                                        base::move(decode_result.left())));
                            }
                        } else {
                            success = true;
                            out.init(base::nullopt);
                        }
                    } else if constexpr (IsDefault<T>::value) {
                        if (optional.hasValue()) {
                            auto decode_result = FieldDecoderType<T>::Type::template decode<DB>(
                                backend, base::move(optional.value()));
                            if (decode_result.isRight()) {
                                e.init(base::move(decode_result.right()));
                            } else {
                                success = true;
                                out.init(base::move(decode_result.left()));
                            }
                        } else {
                            success = true;
                            out.init(in.default_value);
                        }
                    } else {
                        return false;
                    }
                }

                return success && process<i + 1, N, DB, Tuple, L, E, I>(backend, data, t, e, ins);
            }
            template <usize i, usize N, typename DB, typename Tuple, typename L, typename E,
                      typename I>
                requires(i >= N)
            bool process(DB& backend, typename DB::DataType const& data, Tuple& t, E& e,
                         I const& ins) {
                return true;
            }

            template <class F, class Tuple, usize... Is>
            decltype(auto) construct(F func, Tuple&& tuple, std::index_sequence<Is...>) {
                return func(base::move(std::get<Is>(base::forward<Tuple>(tuple)).get())...);
            }
            template <class F, class Tuple>
            decltype(auto) construct(F func, Tuple&& tuple) {
                return construct<F>(
                    func, base::forward<Tuple>(tuple),
                    std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
            }

        }  // namespace _impl

        template <typename R, typename F, DecodeBackend DB, typename... Entries>
        base::Either<R, typename DB::ErrorType> decodeMap(const F& func, DB& backend,
                                                          typename DB::DataType const& data,
                                                          const Entries&... entries) {
            using namespace _impl;
            using ListT = TupleType<Entries...>::Type;
            using Tuple = ListToTuple<ListT>::Type;
            constexpr usize N = sizeof...(Entries);
            Tuple result;
            Uninitialized<typename DB::ErrorType> error;
            bool success =
                process<0, N, DB, Tuple, List<Entries...>, Uninitialized<typename DB::ErrorType>>(
                    backend, data, result, error, std::make_tuple(entries...));
            if (success)
                return base::makeLeft<R, typename DB::ErrorType>(
                    construct<F>(func, base::move(result)));
            else
                return base::makeRight<R, typename DB::ErrorType>(error.get());
        }

    }  // namespace __decode_map

    using __decode_map::DecodeField;

    using __decode_map::decodeMap;

    /*
     * codecs of basic types
     */

    struct CodecNull {
        using Type = base::nullptr_t;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, base::nullptr_t ptr = nullptr) {
            return backend.makeNull();
        }

        template <DecodeBackend DB>
        static base::Either<base::nullptr_t, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            auto result = backend.getNull(data);
            if (result.hasValue()) {
                return base::makeRight<base::nullptr_t, typename DB::ErrorType>(result.value());
            }
            return base::makeLeft<base::nullptr_t, typename DB::ErrorType>(nullptr);
        }
    };

    struct CodecBoolean {
        using Type = bool;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  bool b) {
            return backend.makeBoolean(b);
        }

        template <DecodeBackend DB>
        static base::Either<bool, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            return backend.getBoolean(data);
        }
    };

    struct CodecU8 {
        using Type = u8;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  u8 n) {
            return backend.makeU8(n);
        }

        template <DecodeBackend DB>
        static base::Either<u8, typename DB::ErrorType> decode(DB& backend,
                                                               const typename DB::DataType& data) {
            return backend.getU8(data);
        }
    };

    struct CodecI8 {
        using Type = i8;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  i8 n) {
            return backend.makeI8(n);
        }

        template <DecodeBackend DB>
        static base::Either<i8, typename DB::ErrorType> decode(DB& backend,
                                                               const typename DB::DataType& data) {
            return backend.getI8(data);
        }
    };

    struct CodecU16 {
        using Type = u16;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  u16 n) {
            return backend.makeU16(n);
        }

        template <DecodeBackend DB>
        static base::Either<u16, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getU16(data);
        }
    };

    struct CodecI16 {
        using Type = i16;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  i16 n) {
            return backend.makeI16(n);
        }

        template <DecodeBackend DB>
        static base::Either<i16, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getI16(data);
        }
    };

    struct CodecU32 {
        using Type = u32;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  u32 n) {
            return backend.makeU32(n);
        }

        template <DecodeBackend DB>
        static base::Either<u32, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getU32(data);
        }
    };

    struct CodecI32 {
        using Type = i32;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  i32 n) {
            return backend.makeI32(n);
        }

        template <DecodeBackend DB>
        static base::Either<i32, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getI32(data);
        }
    };

    struct CodecU64 {
        using Type = u64;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  u64 n) {
            return backend.makeU64(n);
        }

        template <DecodeBackend DB>
        static base::Either<u64, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getU64(data);
        }
    };

    struct CodecI64 {
        using Type = i64;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  i64 n) {
            return backend.makeI64(n);
        }

        template <DecodeBackend DB>
        static base::Either<i64, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getI64(data);
        }
    };

    struct CodecF32 {
        using Type = f32;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  f32 v) {
            return backend.makeF32(v);
        }

        template <DecodeBackend DB>
        static base::Either<f32, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getF32(data);
        }
    };

    struct CodecF64 {
        using Type = f64;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(EB& backend,
                                                                                  f64 v) {
            return backend.makeF64(v);
        }

        template <DecodeBackend DB>
        static base::Either<f64, typename DB::ErrorType> decode(DB& backend,
                                                                const typename DB::DataType& data) {
            return backend.getF64(data);
        }
    };

    struct CodecString {
        using Type = base::string;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const base::string& s) {
            return backend.makeString(s);
        }

        template <DecodeBackend DB>
        static base::Either<base::string, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            return backend.getString(data);
        }
    };

    /*
     * useful codecs
     */

    /*
     * Codec of an array of some type
     *
     * CodecArray<Codec> encodes/decodes an array, whose elements are encoded/decoded using
     * Codec.
     */
    template <typename Codec>
        requires Encoder<Codec> || Decoder<Codec>
    struct CodecArray {
        using ChildType = Codec::Type;
        using Type = base::vector<ChildType>;

        template <EncodeBackend EB>
            requires Encoder<Codec>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const Type& array) {
            base::vector<typename EB::DataType> tmp;
            for (const auto& item : array) {
                auto result = Codec::template encode<EB>(backend, item);
                if (result.isRight()) return result;
                tmp.push(base::move(result.left()));
            }

            return backend.makeArray(base::move(tmp));
        }

        template <DecodeBackend DB>
            requires Decoder<Codec>
        static base::Either<Type, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            using ErrorType = DB::ErrorType;

            auto result_array = backend.getArray(data);
            if (result_array.isRight())
                return base::makeRight<Type, ErrorType>(result_array.right());

            Type tmp;
            for (const auto& item : result_array.left()) {
                auto result = Codec::template decode<DB>(backend, item);
                if (result.isRight()) return base::makeRight<Type, ErrorType>(result.right());
                tmp.push(base::move(result.left()));
            }

            return base::makeLeft<Type, ErrorType>(base::move(tmp));
        }
    };

    template <typename F, typename E>
    concept CheckFunctionFor =
        (Encoder<E> || Decoder<E>) && requires(const F& func, const E::Type& v) {
            func(v);
            { func(v) } -> base::SameAs<bool>;
        };

    /*
     * middleware codec that checks if the value to be encoded/decoded value meets certain condition
     */
    template <typename Codec, auto check_func>
        requires(Encoder<Codec> || Decoder<Codec>) && CheckFunctionFor<decltype(check_func), Codec>
    struct CodecCheck {
        using Type = Codec::Type;

        template <EncodeBackend EB>
            requires Encoder<Codec>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const Type& object) {
            if (check_func(object)) {
                return Codec::template encode<EB>(backend, object);
            } else {
                return base::makeRight<typename EB::DataType, typename EB::ErrorType>(
                    "value to be encoded failed the condition check");
            }
        }

        template <DecodeBackend DB>
            requires Decoder<Codec>
        static base::Either<Type, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            auto result = Codec::template decode<DB>(backend, data);
            if (result.isLeft()) {
                if (check_func(result.left())) {
                    return result;
                } else {
                    return base::makeRight<Type, typename DB::ErrorType>(
                        "decoded value failed the condition check");
                }
            } else {
                return result;
            }
        }
    };

    template <typename Codec, Codec::Type v>
    // some compilers (e.g. GCC) will fail if they see '>' here
    using CodecGreaterThan = CodecCheck<Codec, [](const Codec::Type& a) { return !(a <= v); }>;

    template <typename Codec, Codec::Type v>
    using CodecGreaterEqual = CodecCheck<Codec, [](const Codec::Type& a) { return !(a < v); }>;

    template <typename Codec, Codec::Type v>
    using CodecLessThan = CodecCheck<Codec, [](const Codec::Type& a) { return a < v; }>;

    template <typename Codec, Codec::Type v>
    using CodecLessEqual = CodecCheck<Codec, [](const Codec::Type& a) { return a <= v; }>;

    template <typename Codec, Codec::Type min, Codec::Type max>
        requires(min <= max)
    using CodecInRange =
        CodecCheck<Codec, [](const Codec::Type& a) { return a >= min && a <= max; }>;

}  // namespace spargel::codec
