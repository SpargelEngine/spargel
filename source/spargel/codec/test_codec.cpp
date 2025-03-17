#include <spargel/base/check.h>
#include <spargel/base/test.h>
#include <spargel/codec/codec.h>

// libc
#include <math.h>

using namespace spargel;
using namespace spargel::codec;

namespace {

    static_assert(EncoderDecoder<CodecNull>);

    static_assert(EncoderDecoder<CodecBoolean>);

    static_assert(EncoderDecoder<CodecU8>);
    static_assert(EncoderDecoder<CodecI8>);
    static_assert(EncoderDecoder<CodecU16>);
    static_assert(EncoderDecoder<CodecI16>);
    static_assert(EncoderDecoder<CodecU32>);
    static_assert(EncoderDecoder<CodecI32>);
    static_assert(EncoderDecoder<CodecU64>);
    static_assert(EncoderDecoder<CodecI64>);

    static_assert(EncoderDecoder<CodecF32>);
    static_assert(EncoderDecoder<CodecF64>);

    static_assert(EncoderDecoder<CodecString>);

    static_assert(EncoderDecoder<CodecArray<CodecI32>>);
    static_assert(EncoderDecoder<CodecArray<CodecString>>);
    static_assert(EncoderDecoder<CodecArray<CodecArray<CodecI32>>>);
    static_assert(EncoderDecoder<CodecArray<CodecArray<CodecString>>>);
    static_assert(EncoderDecoder<CodecArray<CodecArray<CodecArray<CodecI32>>>>);
    static_assert(EncoderDecoder<CodecArray<CodecArray<CodecArray<CodecString>>>>);

    static_assert(EncoderDecoder<CodecCheck<CodecI32, [](i32 a) { return a < 0; }>>);

    static_assert(EncoderDecoder<CodecGreaterThan<CodecI32, 0>>);
    static_assert(EncoderDecoder<CodecGreaterEqual<CodecI32, 0>>);
    static_assert(EncoderDecoder<CodecLessThan<CodecI32, 0>>);
    static_assert(EncoderDecoder<CodecLessEqual<CodecI32, 0>>);
    // TODO: Clang 16 bug
    //
    // static_assert(EncoderDecoder<CodecGreaterThan<CodecF32, 0.0f>>);
    // static_assert(EncoderDecoder<CodecGreaterEqual<CodecF32, 0.0f>>);
    // static_assert(EncoderDecoder<CodecLessThan<CodecF64, 0.0>>);
    // static_assert(EncoderDecoder<CodecLessEqual<CodecF64, 0.0>>);

    static_assert(EncoderDecoder<CodecInRange<CodecI32, 0, 100>>);
    // TODO: Clang 16 bug
    //
    // static_assert(EncoderDecoder<CodecInRange<CodecF32, 0.0f, 100.0f>>);

    struct TestData {
        u64 value;
    };

    struct EncodeBackendTest {
        using DataType = TestData;
        using ErrorType = CodecError;

        base::Either<TestData, CodecError> makeNull() {
            return base::makeLeft<TestData, CodecError>(0);
        }

        base::Either<TestData, CodecError> makeBoolean(bool b) {
            return base::makeLeft<TestData, CodecError>(b ? 1 : 0);
        }

        base::Either<TestData, CodecError> makeU8(u8 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeI8(i8 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeU16(u16 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeI16(i16 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeU32(u32 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeI32(i32 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeU64(u64 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }
        base::Either<TestData, CodecError> makeI64(i64 n) {
            return base::makeLeft<TestData, CodecError>(n);
        }

        base::Either<TestData, CodecError> makeF32(f32 v) {
            return base::makeLeft<TestData, CodecError>(v);
        }
        base::Either<TestData, CodecError> makeF64(f64 v) {
            return base::makeLeft<TestData, CodecError>(v);
        }

        base::Either<TestData, CodecError> makeString(const base::string& s) {
            return base::makeLeft<TestData, CodecError>((int)s.length());
        }

        base::Either<TestData, CodecError> makeArray(const base::vector<TestData>& array) {
            int sum = 0;
            for (const auto& item : array) sum += item.value;
            return base::makeLeft<TestData, CodecError>(sum);
        }

        base::Either<TestData, CodecError> makeMap(
            const base::HashMap<base::string, TestData>& map) {
            int sum = 0;
            // TODO
            return base::makeLeft<TestData, CodecError>(sum);
        }
    };

    static_assert(EncodeBackend<EncodeBackendTest>);

}  // namespace

TEST(Codec_Encode_Primitive) {
    EncodeBackendTest backend;
    auto result = base::makeRight<TestData, CodecError>("");

    result = CodecNull::encode(backend, {});
    spargel_check(result.isLeft() && result.left().value == 0);

    result = CodecBoolean::encode(backend, true);
    spargel_check(result.isLeft() && result.left().value == 1);
    result = CodecBoolean::encode(backend, false);
    spargel_check(result.isLeft() && result.left().value == 0);

    result = CodecU8::encode(backend, 0);
    spargel_check(result.isLeft() && result.left().value == 0);
    result = CodecU8::encode(backend, 0xff);
    spargel_check(result.isLeft() && result.left().value == 0xff);

    result = CodecI8::encode(backend, -0x80);
    spargel_check(result.isLeft() && (i8)result.left().value == -0x80);
    result = CodecI8::encode(backend, 0x7f);
    spargel_check(result.isLeft() && result.left().value == 0x7f);

    result = CodecU16::encode(backend, 0);
    spargel_check(result.isLeft() && result.left().value == 0);
    result = CodecU16::encode(backend, 0xffff);
    spargel_check(result.isLeft() && result.left().value == 0xffff);

    result = CodecI16::encode(backend, -0x8000);
    spargel_check(result.isLeft() && (i16)result.left().value == -0x8000);
    result = CodecI16::encode(backend, 0x7fff);
    spargel_check(result.isLeft() && result.left().value == 0x7fff);

    result = CodecU32::encode(backend, 0);
    spargel_check(result.isLeft() && result.left().value == 0);
    result = CodecU32::encode(backend, 0xFFFFFFFF);
    spargel_check(result.isLeft() && result.left().value == 0xFFFFFFFF);

    result = CodecI32::encode(backend, -0x80000000);
    spargel_check(result.isLeft() && (i32)result.left().value == (i32)-0x80000000);
    result = CodecI32::encode(backend, 0x7FFFFFFF);
    spargel_check(result.isLeft() && result.left().value == 0x7FFFFFFF);

    result = CodecU64::encode(backend, 0);
    spargel_check(result.isLeft() && result.left().value == 0);
    result = CodecU64::encode(backend, 0x7FFFFFFFFFFFFFFFULL);
    spargel_check(result.isLeft() && result.left().value == 0x7FFFFFFFFFFFFFFFULL);

    result = CodecI64::encode(backend, -0x8000000000000000LL);
    spargel_check(result.isLeft() && (i64)result.left().value == (i64)-0x8000000000000000LL);
    result = CodecI64::encode(backend, 0x7FFFFFFFFFFFFFFFLL);
    spargel_check(result.isLeft() && result.left().value == 0x7FFFFFFFFFFFFFFFLL);

    result = CodecF32::encode(backend, 3.14f);
    spargel_check(result.isLeft() && result.left().value == (u64)3.14f);

    result = CodecF64::encode(backend, 12345.6789);
    spargel_check(result.isLeft() && result.left().value == (u64)12345.6789);

    result = CodecString::encode(backend, base::string("ABC"));
    spargel_check(result.isLeft() && result.left().value == 3);
}

TEST(Codec_Encode_Array) {
    EncodeBackendTest backend;

    {
        base::vector<base::string> v;
        v.push("A");
        v.push("BC");
        v.push("DEF");
        auto result = CodecArray<CodecString>::encode(backend, base::move(v));
        spargel_check(result.isLeft() && result.left().value == 1 + 2 + 3);
    }
    {
        base::vector<base::vector<i32>> v;
        base::vector<i32> v1;
        v1.push(1);
        v1.push(-2);
        v.push(base::move(v1));
        base::vector<i32> v2;
        v2.push(3);
        v2.push(-4);
        v.push(base::move(v2));
        auto result = CodecArray<CodecArray<CodecI32>>::encode(backend, base::move(v));
        spargel_check(result.isLeft() && (i32)result.left().value == (1 + -2) + (3 + -4));
    }
}

TEST(Codec_Encode_Map) {
    EncodeBackendTest backend;

    {
        auto result = encodeMap(backend);
        spargel_check(result.isLeft());
        // TODO
    }
    {
        base::vector<f32> scores;
        scores.push(98);
        scores.push(87.5f);
        scores.push(92);
        auto result =
            encodeMap(backend,  //
                      EncodeField::Normal<CodecString>("name", base::string("Alice")),
                      EncodeField::Normal<CodecU32>("age", 20),
                      EncodeField::Normal<CodecBoolean>("happy", true),
                      EncodeField::Normal<CodecArray<CodecF32>>("scores", base::move(scores)));
        spargel_check(result.isLeft());
        // TODO
    }
}
