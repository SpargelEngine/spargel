#include <spargel/codec/test_json.h>

struct Student {
    base::string type = base::string("normal");
    base::string name;
    base::Optional<base::string> nickname;
    u32 age;
    bool happy;
    base::vector<f32> scores;

    using Constructor = base::Constructor<Student(const base::string&, const base::string&,
                                                  const base::Optional<base::string>&, u32, bool,
                                                  const base::vector<f32>&)>;

    struct Codec {
        using Type = Student;

        template <EncodeBackend EB>
        static base::Either<typename EB::DataType, typename EB::ErrorType> encode(
            EB& backend, const Student& student) {
            // clang-format off
            return encodeMap(backend,
                EncodeField::Normal<CodecString>("type", student.type),
                EncodeField::Normal<CodecString>("name", student.name),
                EncodeField::Optional<CodecString>("nickname", student.nickname),
                EncodeField::Normal<CodecU32>("age", student.age),
                EncodeField::Normal<CodecBoolean>("happy", student.happy),
                // TODO: Clang 16 bug
                //
                // EncodeField::Normal<CodecArray<CodecInRange<CodecF32, 0.0f, 100.0f>>>("scores", student.scores));
                EncodeField::Normal<CodecArray<CodecF32>>("scores", student.scores));
            // clang-format on
        }

        template <DecodeBackend DB>
        static base::Either<Student, typename DB::ErrorType> decode(
            DB& backend, const typename DB::DataType& data) {
            // clang-format off
            return decodeMap<Student>(
                Student::Constructor(), backend, data,
                DecodeField::Default<CodecString>("type", base::string("normal")),
                DecodeField::Required<CodecString>("name"),
                DecodeField::Optional<CodecString>("nickname"),
                DecodeField::Required<CodecU32>("age"),
                DecodeField::Required<CodecBoolean>("happy"),
                // TODO: Clang 16 bug
                //
                // DecodeField::Required<CodecArray<CodecInRange<CodecF32, 0.0f, 100.0f>>>("scores"));
                DecodeField::Required<CodecArray<CodecF32>>("scores"));
            // clang-format on
        }
    };
};

static_assert(Encoder<Student::Codec> && Decoder<Student::Codec>);

TEST(JSON_Codec_Encode_Primitive) {
    EncodeBackendJson backend;
    auto result = base::makeLeft<JsonValue, JsonEncodeError>();

    result = CodecNull::encode(backend);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNull()));

    result = CodecBoolean::encode(backend, true);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonBoolean(true)));

    result = CodecBoolean::encode(backend, false);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonBoolean(false)));

    result = CodecU8::encode(backend, 42);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(42)));

    result = CodecI8::encode(backend, -10);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(-10)));

    result = CodecU16::encode(backend, 65535);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(65535)));

    result = CodecI16::encode(backend, -32768);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(-32768)));

    result = CodecU32::encode(backend, 4294967295);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(4294967295)));

    result = CodecI32::encode(backend, -2147483648);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(-2147483648)));

    result = CodecU64::encode(backend, 18446744073709551615ULL);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(18446744073709551615.0)));

    result = CodecI64::encode(backend, -9223372036854775807LL);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(-9223372036854775807.0)));

    result = CodecF32::encode(backend, 123.456f);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(123.456f)));

    result = CodecF64::encode(backend, 789.012);
    spargel_check(result.isLeft() && isEqual(result.left(), JsonNumber(789.012)));

    result = CodecString::encode(backend, base::string("ABC"));
    spargel_check(result.isLeft() && isEqual(result.left(), JsonString("ABC")));
}

TEST(JSON_Codec_Decode_Primitive) {
    DecodeBackendJson backend;

    {
        auto result = CodecNull::decode(backend, JsonNull());
        spargel_check(result.isLeft());
    }
    {
        auto result = CodecBoolean::decode(backend, JsonBoolean(true));
        spargel_check(result.isLeft() && result.left() == true);
    }
    {
        auto result = CodecBoolean::decode(backend, JsonBoolean(false));
        spargel_check(result.isLeft() && result.left() == false);
    }
    {
        auto result = CodecU8::decode(backend, JsonNumber(255));
        spargel_check(result.isLeft() && result.left() == 255);
    }
    {
        auto result = CodecI8::decode(backend, JsonNumber(-128));
        spargel_check(result.isLeft() && result.left() == -128);
    }
    {
        auto result = CodecU16::decode(backend, JsonNumber(65535));
        spargel_check(result.isLeft() && result.left() == 65535);
    }
    {
        auto result = CodecI16::decode(backend, JsonNumber(-32768));
        spargel_check(result.isLeft() && result.left() == -32768);
    }
    {
        auto result = CodecU32::decode(backend, JsonNumber(4294967295));
        spargel_check(result.isLeft() && result.left() == 4294967295);
    }
    {
        auto result = CodecI32::decode(backend, JsonNumber(-2147483648));
        spargel_check(result.isLeft() && result.left() == -2147483648);
    }
    // JSON cannot handle large integers properly.
    {
        auto result = CodecU64::decode(backend, JsonNumber(123));
        spargel_check(result.isLeft() && result.left() == 123);
    }
    {
        auto result = CodecI64::decode(backend, JsonNumber(-321));
        spargel_check(result.isLeft() && result.left() == -321);
    }
    {
        auto result = CodecF32::decode(backend, JsonNumber(123.456f));
        spargel_check(result.isLeft() && fabs(result.left() - 123.456f) < 1e-6f);
    }
    {
        auto result = CodecF64::decode(backend, JsonNumber(789.012));
        spargel_check(result.isLeft() && fabs(result.left() - 789.012) < 1e-9);
    }
    {
        auto result = CodecString::decode(backend, JsonString("ABC"));
        spargel_check(result.isLeft() && result.left() == base::string("ABC"));
    }
}

TEST(JSON_Codec_Encode_Array) {
    EncodeBackendJson backend;

    {
        base::vector<base::string> v;
        v.push("ABC");
        v.push("123");
        v.push("!@#$");
        auto result = CodecArray<CodecString>::encode(backend, base::move(v));
        spargel_check(result.isLeft() && result.left().type == JsonValueType::array);

        auto& array = result.left().array.elements;
        spargel_check(array.count() == 3);
        spargel_check(isEqual(array[0], JsonString("ABC")));
        spargel_check(isEqual(array[1], JsonString("123")));
        spargel_check(isEqual(array[2], JsonString("!@#$")));
    }
    {
        base::vector<base::vector<i32>> v;
        base::vector<i32> v1;
        v1.push(1);
        v1.push(2);
        v.push(base::move(v1));
        base::vector<i32> v2;
        v2.push(-3);
        v2.push(-4);
        v.push(base::move(v2));
        auto result = CodecArray<CodecArray<CodecI32>>::encode(backend, base::move(v));
        spargel_check(result.isLeft() && result.left().type == JsonValueType::array);

        auto& array = result.left().array.elements;
        spargel_check(array.count() == 2);
        spargel_check(array[0].type == JsonValueType::array);
        spargel_check(array[1].type == JsonValueType::array);
        auto& array1 = array[0].array.elements;
        spargel_check(isEqual(array1[0], JsonNumber(1)));
        spargel_check(isEqual(array1[1], JsonNumber(2)));
        auto& array2 = array[1].array.elements;
        spargel_check(isEqual(array2[0], JsonNumber(-3)));
        spargel_check(isEqual(array2[1], JsonNumber(-4)));
    }
}

TEST(JSON_Codec_Decode_Array) {
    DecodeBackendJson backend;

    {
        auto result_json = parseJson("[123, 456, 789]");
        spargel_check(result_json.isLeft());

        auto result = CodecArray<CodecU32>::decode(backend, base::move(result_json.left()));
        spargel_check(result.isLeft());

        auto& array = result.left();
        spargel_check(array.count() == 3);
        spargel_check(array[0] == 123);
        spargel_check(array[1] == 456);
        spargel_check(array[2] == 789);
    }
    {
        auto result_json = parseJson("[[\"ABC\", \"123\"], [\"XYZ\", \"789\"]]");
        spargel_check(result_json.isLeft());

        auto result =
            CodecArray<CodecArray<CodecString>>::decode(backend, base::move(result_json.left()));
        spargel_check(result.isLeft());

        auto& array = result.left();
        spargel_check(array[0][0] == base::string("ABC"));
        spargel_check(array[0][1] == base::string("123"));
        spargel_check(array[1][0] == base::string("XYZ"));
        spargel_check(array[1][1] == base::string("789"));
    }
}

TEST(JSON_Codec_Encode_Map) {
    EncodeBackendJson backend;

    {
        auto result = encodeMap(backend);
        spargel_check(result.isLeft());
    }
    {
        Student student;
        student.name = "Alice";
        student.age = 20;
        student.happy = true;
        base::vector<f32> scores;
        scores.push(98);
        scores.push(87.5f);
        scores.push(92);
        student.scores = base::move(scores);

        auto result = Student::Codec::encode(backend, base::move(student));
        spargel_check(result.isLeft());

        auto& object = result.left().object;
        spargel_check(isMemberEqual(object, JsonString("type"), JsonString("normal")));
        spargel_check(isMemberEqual(object, JsonString("name"), JsonString("Alice")));
        auto* p_nickname = object.members.get(JsonString("nickname"));
        spargel_check(p_nickname == nullptr);
        spargel_check(isMemberEqual(object, JsonString("age"), JsonNumber(20)));
        spargel_check(isMemberEqual(object, JsonString("happy"), JsonBoolean(true)));
        auto* p_array = object.members.get(JsonString("scores"));
        spargel_check(p_array != nullptr && p_array->type == JsonValueType::array);
        auto& array = p_array->array.elements;
        spargel_check(array.count() == 3);
        spargel_check(isEqual(array[0], JsonNumber(98)));
        spargel_check(isEqual(array[1], JsonNumber(87.5)));
        spargel_check(isEqual(array[2], JsonNumber(92)));
    }
}

TEST(JSON_Codec_Decode_Map) {
    DecodeBackendJson backend;

    {
        const auto str =
            "{\n"
            "  \"name\": \"Alice\",\n"
            "  \"age\": 20,\n"
            "  \"happy\": true,\n"
            "  \"scores\": [98, 87.5, 92]\n"
            "}";
        auto result_json = parseJson(str);
        spargel_check(result_json.isLeft());

        auto result = Student::Codec::decode(backend, base::move(result_json.left()));
        spargel_check(result.isLeft());

        auto& student = result.left();
        spargel_check(student.type == base::string("normal"));
        spargel_check(student.name == base::string("Alice"));
        spargel_check(!student.nickname.hasValue());
        spargel_check(student.age == 20);
        spargel_check(student.happy == true);
        spargel_check(student.scores.count() == 3);
        spargel_check(fabs(student.scores[0] - 98) < 1e-6f);
        spargel_check(fabs(student.scores[1] - 87.5f) < 1e-6f);
        spargel_check(fabs(student.scores[2] - 92) < 1e-6f);
    }
    {
        const auto str =
            "[\n"
            "  {\n"
            "    \"name\": \"Alice\",\n"
            "    \"age\": 20,\n"
            "    \"happy\": true,\n"
            "    \"scores\": [98, 87.5, 92]\n"
            "  },\n"
            "  {\n"
            "    \"name\": \"Bob\",\n"
            "    \"nickname\": \"Bomb\",\n"
            "    \"age\": 18,\n"
            "    \"happy\": false,\n"
            "    \"scores\": [65.5]\n"
            "  },\n"
            "  {\n"
            "    \"type\": \"exchange\",\n"
            "    \"name\": \"David\",\n"
            "    \"age\": 21,\n"
            "    \"happy\": true,\n"
            "    \"scores\": [99, 97.5]\n"
            "  }\n"
            "]";
        auto result_json = parseJson(str);
        spargel_check(result_json.isLeft());

        auto result = CodecArray<Student::Codec>::decode(backend, base::move(result_json.left()));
        spargel_check(result.isLeft());

        auto& students = result.left();

        spargel_check(students[0].type == base::string("normal"));
        spargel_check(students[0].name == base::string("Alice"));
        spargel_check(!students[0].nickname.hasValue());
        spargel_check(students[0].age == 20);
        spargel_check(students[0].happy == true);
        spargel_check(students[0].scores.count() == 3);
        spargel_check(fabs(students[0].scores[0] - 98) < 1e-6f);
        spargel_check(fabs(students[0].scores[1] - 87.5f) < 1e-6f);
        spargel_check(fabs(students[0].scores[2] - 92) < 1e-6f);

        spargel_check(students[1].type == base::string("normal"));
        spargel_check(students[1].name == base::string("Bob"));
        spargel_check(students[1].nickname.hasValue() &&
                      students[1].nickname.value() == base::string("Bomb"));
        spargel_check(students[1].age == 18);
        spargel_check(students[1].happy == false);
        spargel_check(students[1].scores.count() == 1);
        spargel_check(fabs(students[1].scores[0] - 65.5) < 1e-6f);

        spargel_check(students[2].type == base::string("exchange"));
        spargel_check(students[2].name == base::string("David"));
        spargel_check(!students[2].nickname.hasValue());
        spargel_check(students[2].age == 21);
        spargel_check(students[2].happy == true);
        spargel_check(students[2].scores.count() == 2);
        spargel_check(fabs(students[2].scores[0] - 99) < 1e-6f);
        spargel_check(fabs(students[2].scores[1] - 97.5f) < 1e-6f);
    }
}
