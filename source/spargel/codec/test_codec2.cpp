#include <spargel/base/check.h>
#include <spargel/base/test.h>
#include <spargel/codec/codec2.h>

// libc
#include <math.h>

using namespace spargel;
using namespace spargel::codec;

namespace {

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

TEST(Codec2_Encode_Primitive) {
    using EB = EncodeBackendTest;
    EB backend;
    auto result = base::makeRight<TestData, CodecError>("");

    result = EncoderNull<EB>().encode(backend);
    spargel_check(result.isLeft() && result.left().value == 0);

    result = EncoderBoolean<EB>().encode(backend, true);
    spargel_check(result.isLeft() && result.left().value == 1);
    result = EncoderBoolean<EB>().encode(backend, false);
    spargel_check(result.isLeft() && result.left().value == 0);

    result = EncoderI32<EB>().encode(backend, -0x80000000);
    spargel_check(result.isLeft() && (i32)result.left().value == (i32)-0x80000000);
    result = EncoderI32<EB>().encode(backend, 0x7FFFFFFF);
    spargel_check(result.isLeft() && result.left().value == 0x7FFFFFFF);

    result = EncoderString<EB>().encode(backend, base::string("ABC"));
    spargel_check(result.isLeft() && result.left().value == 3);
}

TEST(Codec2_Encode_Array) {
    using EB = EncodeBackendTest;
    EB backend;

    {
        base::vector<base::string> v;
        v.push("A");
        v.push("BC");
        v.push("DEF");
        auto result = EncoderString<EB>().arrayOf().encode(backend, base::move(v));
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
        auto result = EncoderI32<EB>().arrayOf().arrayOf().encode(backend, base::move(v));
        spargel_check(result.isLeft() && (i32)result.left().value == (1 + -2) + (3 + -4));
    }
}
