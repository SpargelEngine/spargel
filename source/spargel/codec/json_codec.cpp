#include <spargel/codec/json.h>

namespace spargel::codec {

    static_assert(EncodeBackend<EncodeBackendJson>);
    static_assert(DecodeBackend<DecodeBackendJson>);

    base::Optional<JsonDecodeError> DecodeBackendJson::getNull(const JsonValue& data) {
        if (data.type != JsonValueType::null) {
            return base::makeOptional<JsonDecodeError>("expected null");
        }
        return base::nullopt;
    }

    base::Either<bool, JsonDecodeError> DecodeBackendJson::getBoolean(const JsonValue& data) {
        if (data.type != JsonValueType::boolean)
            return base::makeRight<bool, JsonDecodeError>("expected a boolean (true/false)");
        else
            return base::makeLeft<bool, JsonDecodeError>(data.boolean);
    }

    const char EXPECTED_NUMBER[] = "expected a number";

    base::Either<u8, JsonDecodeError> DecodeBackendJson::getU8(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<u8, JsonDecodeError>(static_cast<u8>(data.number));
        else
            return base::makeRight<u8, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<i8, JsonDecodeError> DecodeBackendJson::getI8(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<i8, JsonDecodeError>(static_cast<i8>(data.number));
        else
            return base::makeRight<i8, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<u16, JsonDecodeError> DecodeBackendJson::getU16(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<u16, JsonDecodeError>(static_cast<u16>(data.number));
        else
            return base::makeRight<u16, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<i16, JsonDecodeError> DecodeBackendJson::getI16(const JsonValue& data) {
        if (data.type == JsonValueType::number) {
            return base::makeLeft<i16, JsonDecodeError>(static_cast<i16>(data.number));
        } else {
            return base::makeRight<i16, JsonDecodeError>(EXPECTED_NUMBER);
        }
    }
    base::Either<u32, JsonDecodeError> DecodeBackendJson::getU32(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<u32, JsonDecodeError>(static_cast<u32>(data.number));
        else
            return base::makeRight<u32, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<i32, JsonDecodeError> DecodeBackendJson::getI32(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<i32, JsonDecodeError>(static_cast<i32>(data.number));
        else
            return base::makeRight<i32, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<u64, JsonDecodeError> DecodeBackendJson::getU64(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<u64, JsonDecodeError>(static_cast<u64>(data.number));
        else
            return base::makeRight<u64, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<i64, JsonDecodeError> DecodeBackendJson::getI64(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<i64, JsonDecodeError>(static_cast<i64>(data.number));
        else
            return base::makeRight<i64, JsonDecodeError>(EXPECTED_NUMBER);
    }

    base::Either<f32, JsonDecodeError> DecodeBackendJson::getF32(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<f32, JsonDecodeError>(static_cast<f32>(data.number));
        else
            return base::makeRight<f32, JsonDecodeError>(EXPECTED_NUMBER);
    }
    base::Either<f64, JsonDecodeError> DecodeBackendJson::getF64(const JsonValue& data) {
        if (data.type == JsonValueType::number)
            return base::makeLeft<f64, JsonDecodeError>(static_cast<f64>(data.number));
        else
            return base::makeRight<f64, JsonDecodeError>(EXPECTED_NUMBER);
    }

    base::Either<base::string, JsonDecodeError> DecodeBackendJson::getString(
        const JsonValue& data) {
        if (data.type == JsonValueType::string)
            return base::makeLeft<base::string, JsonDecodeError>(data.string);
        else
            return base::makeRight<base::string, JsonDecodeError>("expected a string");
    }

    base::Either<base::vector<JsonValue>, JsonDecodeError> DecodeBackendJson::getArray(
        const JsonValue& data) {
        if (data.type == JsonValueType::array)
            return base::makeLeft<base::vector<JsonValue>, JsonDecodeError>(data.array.elements);
        else
            return base::makeRight<base::vector<JsonValue>, JsonDecodeError>("expected an array");
    }

    base::Either<base::Optional<JsonValue>, JsonDecodeError> DecodeBackendJson::getMember(
        const JsonValue& data, const base::string& key) {
        if (data.type == JsonValueType::object) {
            auto* ptr = data.object.members.get(key);
            base::Optional<JsonValue> optional = base::nullopt;
            if (ptr != nullptr) optional = base::makeOptional<JsonValue>(*ptr);
            return base::makeLeft<base::Optional<JsonValue>, JsonDecodeError>(base::move(optional));
        } else {
            return base::makeRight<base::Optional<JsonValue>, JsonDecodeError>(
                "expected an object");
        }
    }

}  // namespace spargel::codec
