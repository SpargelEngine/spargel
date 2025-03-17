#include <spargel/codec/json.h>
#include <spargel/resource/directory.h>

/* libc */
#include <stdio.h>

using namespace spargel;
using namespace spargel::codec;

namespace {

    void dumpValue(const JsonValue& value);

    void dumpObject(const JsonObject& object) { printf("{TODO}"); }

    void dumpArray(const JsonArray& array) {
        putchar('[');
        putchar(' ');
        usize count = array.elements.count();
        for (usize i = 0; i < count; i++) {
            dumpValue(array.elements[i]);
            if (i < count - 1) {
                putchar(',');
                putchar(' ');
            }
        }
        putchar(' ');
        putchar(']');
    }

    void dumpString(const JsonString& string) {
        putchar('"');
        printf("%s", string.data());
        putchar('"');
    }

    void dumpValue(const JsonValue& value) {
        switch (value.type) {
        case JsonValueType::object:
            dumpObject(value.object);
            break;
        case JsonValueType::array:
            dumpArray(value.array);
            break;
        case JsonValueType::string:
            dumpString(value.string);
            break;
        case JsonValueType::number:
            printf("%lf", value.number);
            break;
        case JsonValueType::boolean:
            printf(value.boolean ? "true" : "false");
            break;
        case JsonValueType::null:
            printf("null");
            break;
        }
    }

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    auto manager = resource::ResourceManagerDirectory("");
    auto optional = manager.open(resource::ResourceId(base::string(argv[1])));
    if (!optional.hasValue()) {
        fprintf(stderr, "Cannot open file \"%s\"\n", argv[1]);
        return 1;
    }
    auto resource = base::move(optional.value());

    auto result = parseJson((char*)resource->mapData(), resource->size());
    if (result.isLeft()) {
        dumpValue(base::move(result.left()));
        putchar('\n');
    } else {
        fprintf(stderr, "Failed to parse JSON: %s\n", result.right().message().data());
    }

    return 0;
}
