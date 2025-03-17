#pragma once

#include <spargel/base/hash_map.h>
#include <spargel/base/optional.h>
#include <spargel/base/string.h>
#include <spargel/base/vector.h>
#include <spargel/codec/codec.h>

namespace spargel::codec {

    enum class JsonValueType {
        object,
        array,
        string,
        number,
        boolean,
        null,
    };

    struct JsonNull {};

    using JsonString = base::string;

    using JsonNumber = double;

    using JsonBoolean = bool;

    class JsonValue;

    struct JsonObject {
        base::HashMap<JsonString, JsonValue> members;

        JsonObject() : members(base::default_allocator()) {}

        JsonObject(const base::HashMap<JsonString, JsonValue>& members) : members(members) {}
        JsonObject(base::HashMap<JsonString, JsonValue>&& members) : members(base::move(members)) {}
    };

    struct JsonArray {
        base::vector<JsonValue> elements;
    };

    // TODO: change to tagged union?
    class JsonValue {
    public:
        JsonValueType type;
        union {
            JsonObject object;
            JsonArray array;
            JsonString string;
            JsonNumber number;
            JsonBoolean boolean;
        };

        JsonValue() : type(JsonValueType::null) {}

        JsonValue(JsonNull&& null) : type(JsonValueType::null) {}
        JsonValue(JsonObject&& object) : type(JsonValueType::object), object(base::move(object)) {}
        JsonValue(JsonArray&& array) : type(JsonValueType::array), array(base::move(array)) {}
        JsonValue(JsonString&& string) : type(JsonValueType::string), string(base::move(string)) {}
        JsonValue(JsonNumber&& number) : type(JsonValueType::number), number(base::move(number)) {}
        JsonValue(JsonBoolean&& boolean)
            : type(JsonValueType::boolean), boolean(base::move(boolean)) {}

        JsonValue(const JsonValue& other);

        JsonValue(JsonValue&& other);

        JsonValue& operator=(const JsonValue& other);

        JsonValue& operator=(JsonValue&& other);

        ~JsonValue() { destroy(); }

    private:
        void destroy();

        void construct_from(const JsonValue& other);

        void move_from(JsonValue&& other);
    };

    class JsonParseError : public CodecError {};

    /*
     * Parser
     */

    base::Either<JsonValue, JsonParseError> parseJson(const char* str, usize length);

    /*
     * Codec Backend
     *
     * Note: due to floating point errors, JSON backend cannot properly handle large integers
     * (U64/I64). For large integers, use strings to represent them.
     */

    class JsonEncodeError : public CodecError {};
    class JsonDecodeError : public CodecError {};

    // JSON encode backend
    struct EncodeBackendJson {
        using DataType = JsonValue;
        using ErrorType = JsonEncodeError;

        base::Either<JsonValue, JsonEncodeError> makeNull() {
            return base::makeLeft<JsonValue, JsonEncodeError>(JsonNull());
        }

        base::Either<JsonValue, JsonEncodeError> makeBoolean(bool b) {
            return base::makeLeft<JsonBoolean, JsonEncodeError>(JsonBoolean(b));
        }

        base::Either<JsonValue, JsonEncodeError> makeU8(u8 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeI8(i8 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeU16(u16 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeI16(i16 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeU32(u32 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeI32(i32 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeU64(u64 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }
        base::Either<JsonValue, JsonEncodeError> makeI64(i64 n) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(n);
        }

        base::Either<JsonValue, JsonEncodeError> makeF32(f32 v) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(v);
        }
        base::Either<JsonValue, JsonEncodeError> makeF64(f64 v) {
            return base::makeLeft<JsonNumber, JsonEncodeError>(v);
        }

        base::Either<JsonValue, JsonEncodeError> makeString(const base::string& s) {
            return base::makeLeft<JsonString, JsonEncodeError>(s);
        }

        base::Either<JsonValue, JsonEncodeError> makeArray(const base::vector<JsonValue>& array) {
            return base::makeLeft<JsonArray, JsonEncodeError>(array);
        }

        base::Either<JsonValue, JsonEncodeError> makeMap(
            const base::HashMap<base::string, JsonValue>& map) {
            return base::makeLeft<JsonObject, JsonEncodeError>(map);
        }
    };

    // JSON decode backend
    struct DecodeBackendJson {
        using DataType = JsonValue;
        using ErrorType = JsonDecodeError;

        base::Optional<JsonDecodeError> getNull(const JsonValue& data);

        base::Either<bool, JsonDecodeError> getBoolean(const JsonValue& data);

        base::Either<u8, JsonDecodeError> getU8(const JsonValue& data);
        base::Either<i8, JsonDecodeError> getI8(const JsonValue& data);
        base::Either<u16, JsonDecodeError> getU16(const JsonValue& data);
        base::Either<i16, JsonDecodeError> getI16(const JsonValue& data);
        base::Either<u32, JsonDecodeError> getU32(const JsonValue& data);
        base::Either<i32, JsonDecodeError> getI32(const JsonValue& data);
        base::Either<u64, JsonDecodeError> getU64(const JsonValue& data);
        base::Either<i64, JsonDecodeError> getI64(const JsonValue& data);

        base::Either<f32, JsonDecodeError> getF32(const JsonValue& data);
        base::Either<f64, JsonDecodeError> getF64(const JsonValue& data);

        base::Either<base::string, JsonDecodeError> getString(const JsonValue& data);

        base::Either<base::vector<JsonValue>, JsonDecodeError> getArray(const JsonValue& data);

        base::Either<base::Optional<JsonValue>, JsonDecodeError> getMember(const JsonValue& data,
                                                                           const base::string& key);
    };

}  // namespace spargel::codec
