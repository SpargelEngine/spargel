#pragma once

#include <spargel/base/check.h>
#include <spargel/base/test.h>
#include <spargel/codec/json.h>

// libc
#include <string.h>

// libm
#include <math.h>

using namespace spargel;
using namespace spargel::codec;

namespace {

    base::Either<JsonValue, JsonParseError> parseJson(const char* str) {
        return codec::parseJson(str, strlen(str));
    }

    bool isEqual(const JsonValue& v1, const JsonValue& v2) {
        if (&v1 == &v2) return true;
        if (v1.type != v2.type) return false;

        switch (v1.type) {
        case JsonValueType::string:
            return v1.string == v2.string;
        case JsonValueType::number:
            return abs(v1.number - v2.number) < 1e-9;
        case JsonValueType::boolean:
            return v1.boolean == v2.boolean;
        case JsonValueType::null:
            return true;
        default:
            return false;
        }
    }

    bool isMemberEqual(JsonObject& object, const JsonString& key, const JsonValue& v) {
        auto* ptr = object.members.get(key);
        if (ptr == nullptr) return false;

        return isEqual(*ptr, v);
    }

}  // namespace
