/*
 * This implementation was inspired by https://github.com/Mojang/DataFixerUpper.
 * See LICENCE_Mojang_DataFixerUpper.
 */

#pragma once

#include <spargel/base/tuple.h>
#include <spargel/base/unique_ptr.h>
#include <spargel/codec/codec.h>

namespace spargel::codec {

    template <EncodeBackend EB, typename T>
    class EncoderArray;

    template <EncodeBackend EB, typename T>
    class Encoder2 {
    public:
        using DataType = EB::DataType;
        using ErrorType = EB::ErrorType;

        virtual ~Encoder2() = default;

        virtual base::Either<DataType, ErrorType> encode(EB& backend, const T& object) const = 0;

        virtual base::unique_ptr<Encoder2> clone() const = 0;

        EncoderArray<EB, T> arrayOf() { return EncoderArray<EB, T>(clone()); }
    };

    template <EncodeBackend EB>
    class EncoderNull : public Encoder2<EB, base::nullptr_t> {
    public:
        base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const base::nullptr_t& ptr = nullptr) const override {
            return backend.makeNull();
        }

        base::unique_ptr<Encoder2<EB, base::nullptr_t>> clone() const override {
            return base::make_unique<EncoderNull<EB>>(*this);
        }
    };

    template <EncodeBackend EB>
    class EncoderBoolean : public Encoder2<EB, bool> {
    public:
        base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const bool& b) const override {
            return backend.makeBoolean(b);
        }

        base::unique_ptr<Encoder2<EB, bool>> clone() const override {
            return base::make_unique<EncoderBoolean<EB>>(*this);
        }
    };

    template <EncodeBackend EB>
    class EncoderI32 : public Encoder2<EB, i32> {
    public:
        base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const i32& n) const override {
            return backend.makeI32(n);
        }

        base::unique_ptr<Encoder2<EB, i32>> clone() const override {
            return base::make_unique<EncoderI32<EB>>(*this);
        }
    };

    template <EncodeBackend EB>
    class EncoderString : public Encoder2<EB, base::string> {
    public:
        base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const base::string& s) const override {
            return backend.makeString(s);
        }

        base::unique_ptr<Encoder2<EB, base::string>> clone() const override {
            return base::make_unique<EncoderString<EB>>(*this);
        }
    };

    template <EncodeBackend EB, typename T>
    class EncoderArray : public Encoder2<EB, base::vector<T>> {
        using DataType = EB::DataType;
        using ErrorType = EB::ErrorType;

    public:
        EncoderArray(base::unique_ptr<Encoder2<EB, T>>&& encoder) : _encoder(base::move(encoder)) {}

        base::Either<DataType, ErrorType> encode(
            EB& backend, const base::vector<T>& v) const override {
            base::vector<DataType> array;
            for (auto& item : v) {
                auto result = _encoder->encode(backend, item);
                if (result.isRight()) return base::Right(base::move(result.right()));
                array.push(base::move(result.left()));
            }
            return backend.makeArray(base::move(array));
        }

        base::unique_ptr<Encoder2<EB, base::vector<T>>> clone() const override {
            return base::make_unique<EncoderArray>(_encoder->clone());
        }

    private:
        base::unique_ptr<Encoder2<EB, T>> _encoder;
    };

    template <EncodeBackend EB, DecodeBackend DB>
    struct CodecBackend {
        EB encodeBackend;
        DB decodeBackend;
    };

}  // namespace spargel::codec
