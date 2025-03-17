#include <spargel/base/either.h>
#include <spargel/base/optional.h>
#include <spargel/codec/cursor.h>
#include <spargel/codec/json.h>

// libm
#include <math.h>

namespace spargel::codec {

    JsonValue::JsonValue(const JsonValue& other) { construct_from(other); }

    JsonValue::JsonValue(JsonValue&& other) { move_from(base::move(other)); }

    JsonValue& JsonValue::operator=(const JsonValue& other) {
        if (this != &other) {
            destroy();
            construct_from(other);
        }
        return *this;
    }

    JsonValue& JsonValue::operator=(JsonValue&& other) {
        if (this != &other) {
            destroy();
            move_from(base::move(other));
        }
        return *this;
    }

    void JsonValue::destroy() {
        switch (type) {
        case JsonValueType::object:
            object.~JsonObject();
            break;
        case JsonValueType::array:
            array.~JsonArray();
            break;
        case JsonValueType::string:
            string.~JsonString();
            break;
        case JsonValueType::number:
            number.~JsonNumber();
            break;
        case JsonValueType::boolean:
            boolean.~JsonBoolean();
            break;
        case JsonValueType::null:
            break;
        }
        type = JsonValueType::null;
    }

    void JsonValue::construct_from(const JsonValue& other) {
        switch (other.type) {
        case JsonValueType::object:
            base::construct_at(&object, other.object);
            break;
        case JsonValueType::array:
            base::construct_at(&array, other.array);
            break;
        case JsonValueType::string:
            base::construct_at(&string, other.string);
            break;
        case JsonValueType::number:
            base::construct_at(&number, other.number);
            break;
        case JsonValueType::boolean:
            base::construct_at(&boolean, other.boolean);
            break;
        case JsonValueType::null:
            break;
        }
        type = other.type;
    }

    void JsonValue::move_from(JsonValue&& other) {
        switch (other.type) {
        case JsonValueType::object:
            base::construct_at(&object, base::move(other.object));
            break;
        case JsonValueType::array:
            base::construct_at(&array, base::move(other.array));
            break;
        case JsonValueType::string:
            base::construct_at(&string, base::move(other.string));
            break;
        case JsonValueType::number:
            base::construct_at(&number, base::move(other.number));
            break;
        case JsonValueType::boolean:
            base::construct_at(&boolean, base::move(other.boolean));
            break;
        case JsonValueType::null:
            break;
        }
        type = other.type;
    }

    namespace {

        using base::Either;
        using base::Optional;
        using base::string;

        using base::makeLeft;
        using base::makeOptional;
        using base::makeRight;
        using base::nullopt;

        const auto UNEXPECTED_END = JsonParseError("unexpected end");

        string char2hex(char ch) {
            const char hexDigits[] = "0123456789abcdef";
            return string(hexDigits[(ch >> 4) & 0xf]) + hexDigits[ch & 0xf];
        }

        void appendUtf8(base::vector<char>& chars, u32 code) {
            if (code <= 0x7f) {
                chars.push(code);
            } else if (code <= 0x7ff) {
                chars.push(0xc0 | (code >> 6));
                chars.push(0x80 | (code & 0x3f));
            } else if (code <= 0xffff) {
                chars.push(0xe0 | (code >> 12));
                chars.push(0x80 | ((code >> 6) & 0x3f));
                chars.push(0x80 | (code & 0x3f));
            } else if (code <= 0x10ffff) {
                chars.push(0xf0 | (code >> 18));
                chars.push(0x80 | ((code >> 12) & 0x3f));
                chars.push(0x80 | ((code >> 6) & 0x3f));
                chars.push(0x80 | (code & 0x3f));
            }
        }

        struct JsonParseContext {
            Cursor cursor;
        };

        Either<JsonValue, JsonParseError> parseValue(JsonParseContext& ctx);
        Either<JsonObject, JsonParseError> parseObject(JsonParseContext& ctx);
        Either<JsonArray, JsonParseError> parseArray(JsonParseContext& ctx);
        Either<JsonString, JsonParseError> parseString(JsonParseContext& ctx);
        Either<JsonNumber, JsonParseError> parseNumber(JsonParseContext& ctx);
        Either<JsonBoolean, JsonParseError> parseBoolean(JsonParseContext& ctx);
        Optional<JsonParseError> parseNull(JsonParseContext& ctx);
        Either<JsonObject, JsonParseError> parseMembers(JsonParseContext& ctx);
        Optional<JsonParseError> parseMember(JsonParseContext& ctx, JsonString& key,
                                             JsonValue& value);
        Either<JsonArray, JsonParseError> parseElements(JsonParseContext& ctx);
        Either<JsonValue, JsonParseError> parseElement(JsonParseContext& ctx);

        /*
         * The syntax descriptions in the following comments are from:
         *   https://www.json.org/json-en.html
         * The actual syntax we are using is slightly different from it.
         */

        /*
         * ws:
         *   ""
         *   '0020' ws
         *   '000A' ws
         *   '000D' ws
         *   '0009' ws
         */
        void eatWhitespaces(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;
            while (!cursorIsEnd(cursor)) {
                char ch = cursorPeek(cursor);
                if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
                    cursorAdvance(cursor);
                else
                    break;
            }
        }

        /*
         * value:
         *   object
         *   array
         *   string
         *   number
         *   "true"
         *   "false"
         *   "null"
         */
        Either<JsonValue, JsonParseError> parseValue(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;
            if (cursorIsEnd(cursor))
                return makeRight<JsonValue, JsonParseError>("expected a value");

            char ch = cursorPeek(cursor);
            switch (ch) {
            case '{':
                /* object */
                return parseObject(ctx);
            case '[':
                /* array */
                return parseArray(ctx);
            case '"':
                /* string */
                return parseString(ctx);
            case 't':
            case 'f':
                /* boolean: true/false */
                return parseBoolean(ctx);
            case 'n': {
                /* null */
                auto result = parseNull(ctx);
                if (result.hasValue())
                    return makeRight<JsonValue, JsonParseError>(base::move(result.value()));
                else
                    return makeLeft<JsonValue, JsonParseError>();
            }
            default:
                /* number */
                if ((ch >= '0' && ch <= '9') || ch == '-') {
                    return parseNumber(ctx);
                } else {
                    return makeRight<JsonValue, JsonParseError>(string("unexpected character: '") +
                                                                ch + '\'');
                }
            }
        }

        /*
         * object:
         *   '{' ws '}'
         *   '{' members '}'
         */
        Either<JsonObject, JsonParseError> parseObject(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            // '{' ws
            if (!cursorTryEatChar(cursor, '{')) {
                return makeRight<JsonObject, JsonParseError>("expected a value");
            }
            eatWhitespaces(ctx);
            if (cursorIsEnd(cursor)) return makeRight<JsonObject, JsonParseError>(UNEXPECTED_END);

            // '}'
            if (cursorTryEatChar(cursor, '}')) return makeLeft<JsonObject, JsonParseError>();

            // members '}'
            auto result = parseMembers(ctx);
            if (result.isRight()) return result;
            if (!cursorTryEatChar(cursor, '}'))
                return makeRight<JsonObject, JsonParseError>("expected '}'");

            return result;
        }

        /*
         * array:
         *   '[' ws ']'
         *   '[' elements ']'
         */
        Either<JsonArray, JsonParseError> parseArray(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            // '[' ws
            if (!cursorTryEatChar(cursor, '['))
                return makeRight<JsonArray, JsonParseError>("expected '['");
            eatWhitespaces(ctx);
            if (cursorIsEnd(cursor)) return makeRight<JsonArray, JsonParseError>(UNEXPECTED_END);

            // ']'
            if (cursorTryEatChar(cursor, ']')) return makeLeft<JsonArray, JsonParseError>();

            // elements ']'
            auto result = parseElements(ctx);
            if (result.isRight()) return result;
            if (!cursorTryEatChar(cursor, ']'))
                return makeRight<JsonArray, JsonParseError>("expected ']'");

            return result;
        }

        bool isGood(char c, char d) {
            return (c != '"' && d != '"') && (c != '\\' && d != '\\') && (c >= 0x20 && d >= 0x20);
        }

        /*
         * string:
         *   '"' characters '"'
         * character
         *   '0020' . '10FFFF' - '"' - '\'
         *   '\' escape
         *
         * escape:
         *   '"'
         *   '\'
         *   '/'
         *   'b'
         *   'f'
         *   'n'
         *   'r'
         *   't'
         *   'u' hex hex hex hex
         *
         * hex:
         *   digit
         *   'A' . 'F'
         *   'a' . 'f'
         */
        Either<JsonString, JsonParseError> parseString(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            // '"'
            if (!cursorTryEatChar(cursor, '"'))
                return makeRight<JsonString, JsonParseError>("expected '\"'");

            // characters
            base::vector<char> chars;
            bool has_escape = false;
            char const* begin = cursorGetPtr(cursor);

            while (!cursorIsEnd(cursor)) {
                char ch = cursorGetChar(cursor);
                char ch2 = cursorGetChar(cursor);

                if (isGood(ch, ch2)) [[likely]] {
                    if (has_escape) {
                        chars.push(ch);
                        chars.push(ch2);
                    }
                    continue;
                } else {
                    // FIXME
                    cursor.cur--;
                }

                // '"'
                if (ch == '"') {
                    if (!has_escape)
                        return makeLeft<JsonString, JsonParseError>(
                            base::string_from_range(begin, cursorGetPtr(cursor) - 1));

                    return makeLeft<JsonString, JsonParseError>(
                        base::string_from_range(chars.begin(), chars.end()));
                }

                // '\'
                if (ch == '\\') {
                    has_escape = true;
                    if (cursorIsEnd(cursor))
                        return makeRight<JsonString, JsonParseError>("unfinished escape");

                    ch = cursorGetChar(cursor);
                    switch (ch) {
                    case '\"':
                    case '\\':
                    case '/':  // why escape this?
                        chars.push(ch);
                        break;
                    case 'b':
                        chars.push('\b');
                        break;
                    case 'f':
                        chars.push('\f');
                        break;
                    case 'n':
                        chars.push('\n');
                        break;
                    case 'r':
                        chars.push('\r');
                        break;
                    case 't':
                        chars.push('\t');
                        break;
                    case 'u': {
                        // TODO: unicode
                        u16 code = 0;
                        for (int i = 0; i < 4; i++) {
                            if (cursorIsEnd(cursor))
                                return makeRight<JsonString, JsonParseError>(
                                    "expected a hex digit");
                            ch = cursorGetChar(cursor);
                            u8 v;
                            if ('0' <= ch && ch <= '9')
                                v = ch - '0';
                            else if ('A' <= ch && ch <= 'F')
                                v = ch - 'A' + 0xa;
                            else if ('a' <= ch && ch <= 'f')
                                v = ch - 'a' + 0xa;
                            else
                                return makeRight<JsonString, JsonParseError>("bad hex digit");
                            code = code * 0x10 + v;
                        }
                        appendUtf8(chars, code);
                    } break;
                    default:
                        return makeRight<JsonString, JsonParseError>(
                            string("unexpected escape character: '") + ch + '\'');
                    }
                } else if ((u8)ch >= 0x20) {
                    // TODO: unicode
                    // no problem for UTF-8
                    chars.push(ch);
                } else {
                    return makeRight<JsonString, JsonParseError>(string("invalid character 0x") +
                                                                 char2hex(ch));
                }
            }

            return makeRight<JsonString, JsonParseError>(UNEXPECTED_END);
        }

        /*
         * integer:
         *   digit
         *   onenine digits
         *   '-' digit
         *   '-' onenine digits
         *
         * digits:
         *   digit
         *   digit digits
         *
         * digit:
         *   '0'
         *   onenine
         *
         * onenine:
         *   '1' . '9'
         */
        Optional<JsonParseError> parseInteger(JsonParseContext& ctx, JsonNumber& number,
                                              bool& minus) {
            auto& cursor = ctx.cursor;
            if (cursorIsEnd(cursor)) return makeOptional<JsonParseError>(UNEXPECTED_END);

            minus = false;
            char ch = cursorPeek(cursor);

            // '-'
            if (ch == '-') {
                minus = true;
                cursorAdvance(cursor);
                ch = cursorPeek(cursor);
            }

            // digit
            if (ch == '0') {
                cursorAdvance(cursor);
                return nullopt;
            }

            // digit
            // onenine digits
            if ('0' < ch && ch <= '9') {
                number = (ch - '0');
                cursorAdvance(cursor);
                while (!cursorIsEnd(cursor)) {
                    ch = cursorPeek(cursor);
                    if ('0' <= ch && ch <= '9') {
                        number = number * 10 + (ch - '0');
                        cursorAdvance(cursor);
                    } else {
                        break;
                    }
                }

                return nullopt;
            }

            return makeOptional<JsonParseError>("expected a number");
        }

        /*
         * fraction:
         *   ""
         *   '.' digits
         */
        Optional<JsonParseError> parseFraction(JsonParseContext& ctx, JsonNumber& number) {
            auto& cursor = ctx.cursor;
            if (cursorIsEnd(cursor)) return nullopt;

            // '.'
            if (cursorPeek(cursor) != '.') return nullopt;
            cursorAdvance(cursor);

            // digits
            char ch = cursorPeek(cursor);
            if (!('0' <= ch && ch <= '9'))
                return makeOptional<JsonParseError>("expected fractional part");
            JsonNumber x = 0.1;
            while (!cursorIsEnd(cursor)) {
                ch = cursorPeek(cursor);
                if ('0' <= ch && ch <= '9') {
                    number += x * (ch - '0');
                    x *= 0.1;
                    cursorAdvance(cursor);
                } else {
                    break;
                }
            }

            return nullopt;
        }

        /*
         * exponent:
         *   ""
         *   'E' sign digits
         *   'e' sign digits
         *
         * sign:
         *   ""
         *   '+'
         *   '-'
         */
        Optional<JsonParseError> parseExponent(JsonParseContext& ctx, JsonNumber& number) {
            auto& cursor = ctx.cursor;

            if (!cursorTryEatChar(cursor, 'E') && !cursorTryEatChar(cursor, 'e')) return nullopt;

            bool minus = false;
            if (cursorTryEatChar(cursor, '-')) {
                minus = true;
            } else if (cursorTryEatChar(cursor, '+')) {
                // skip
            }

            // digits
            char ch = cursorPeek(cursor);
            if (!('0' <= ch && ch <= '9'))
                return makeOptional<JsonParseError>("expected exponential part");
            JsonNumber exponent = 0;
            while (!cursorIsEnd(cursor)) {
                ch = cursorPeek(cursor);
                if ('0' <= ch && ch <= '9') {
                    exponent = exponent * 10 + (ch - '0');
                    cursorAdvance(cursor);
                } else {
                    break;
                }
            }

            if (minus)
                number *= pow(0.1, exponent);
            else
                number *= pow(10, exponent);

            return nullopt;
        }

        /*
         * number:
         *   integer fraction exponent
         */
        Either<JsonNumber, JsonParseError> parseNumber(JsonParseContext& ctx) {
            JsonNumber number(0);
            bool minus;
            auto result = parseInteger(ctx, number, minus);
            if (result.hasValue())
                return makeRight<JsonNumber, JsonParseError>(base::move(result.value()));

            result = parseFraction(ctx, number);
            if (result.hasValue())
                return makeRight<JsonNumber, JsonParseError>(base::move(result.value()));

            result = parseExponent(ctx, number);
            if (result.hasValue())
                return makeRight<JsonNumber, JsonParseError>(base::move(result.value()));

            if (minus) number = -number;

            return makeLeft<JsonNumber, JsonParseError>(base::move(number));
        }

        /*
         *   "true"
         *   "false"
         */
        Either<JsonBoolean, JsonParseError> parseBoolean(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            if (cursorTryEatString(cursor, "true")) {
                return makeLeft<JsonBoolean, JsonParseError>(true);
            } else if (cursorTryEatString(cursor, "false")) {
                return makeLeft<JsonBoolean, JsonParseError>(false);
            } else {
                return makeRight<JsonBoolean, JsonParseError>("expected \"true\" or \"false\"");
            }
        }

        /*
         *   "null"
         */
        Optional<JsonParseError> parseNull(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            if (cursorTryEatString(cursor, "null"))
                return nullopt;
            else
                return makeOptional<JsonParseError>("expected \"null\"");
        }

        /*
         * members:
         *   member
         *   member ',' members
         */
        Either<JsonObject, JsonParseError> parseMembers(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            base::HashMap<JsonString, JsonValue> members(base::default_allocator());
            while (!cursorIsEnd(cursor)) {
                // member
                JsonString key;
                JsonValue value;
                auto result = parseMember(ctx, key, value);
                if (result.hasValue())
                    return makeRight<JsonObject, JsonParseError>(base::move(result.value()));

                members.set(base::move(key), base::move(value));

                // ','
                if (!cursorTryEatChar(cursor, ','))
                    return makeLeft<JsonObject, JsonParseError>(JsonObject(base::move(members)));
            }

            return makeRight<JsonObject, JsonParseError>(UNEXPECTED_END);
        }

        /*
         * member:
         *   ws string ws ':' element
         */
        Optional<JsonParseError> parseMember(JsonParseContext& ctx, JsonString& key,
                                             JsonValue& value) {
            auto& cursor = ctx.cursor;

            // ws
            eatWhitespaces(ctx);

            // string
            auto result_key = parseString(ctx);
            if (result_key.isRight())
                return makeOptional<JsonParseError>(base::move(result_key.right()));
            key = base::move(result_key.left());

            // ws
            eatWhitespaces(ctx);

            // ':'
            if (!cursorTryEatChar(cursor, ':')) return makeOptional<JsonParseError>("expected ':'");

            // element
            auto result_value = parseElement(ctx);
            if (result_value.isRight())
                return makeOptional<JsonParseError>(base::move(result_value.right()));
            value = base::move(result_value.left());

            return nullopt;
        }

        /*
         * elements:
         *   element
         *   element ',' elements
         */
        Either<JsonArray, JsonParseError> parseElements(JsonParseContext& ctx) {
            auto& cursor = ctx.cursor;

            base::vector<JsonValue> elements;
            while (!cursorIsEnd(cursor)) {
                // element
                auto result = parseElement(ctx);
                if (result.isRight())
                    return makeRight<JsonArray, JsonParseError>(base::move(result.right()));

                elements.push(base::move(result.left()));

                // ','
                if (!cursorTryEatChar(cursor, ','))
                    return makeLeft<JsonArray, JsonParseError>(JsonArray(base::move(elements)));
            }

            return makeRight<JsonArray, JsonParseError>(UNEXPECTED_END);
        }

        /*
         * element:
         *   ws value ws
         */
        Either<JsonValue, JsonParseError> parseElement(JsonParseContext& ctx) {
            // ws
            eatWhitespaces(ctx);

            // value
            auto result = parseValue(ctx);
            if (result.isRight()) return result;

            // ws
            eatWhitespaces(ctx);

            return result;
        }

    }  // namespace

    Either<JsonValue, JsonParseError> parseJson(const char* str, usize length) {
        JsonParseContext ctx;
        ctx.cursor.cur = str;
        ctx.cursor.end = str + length;
        return parseElement(ctx);
    }

}  // namespace spargel::codec
