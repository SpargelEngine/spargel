#include <spargel/base/assert.h>
#include <spargel/util/path.h>

using namespace spargel;

static bool dirname_equal(const char* path, const char* expected) {
    auto path_dirname = util::dirname(base::string(path));
    return path_dirname == base::string(expected);
}

void test_dirname() {
    // absolute
#if SPARGEL_IS_WINDOWS

    // TODO
    spargel_assert(dirname_equal("C:\\hello\\world").length() == 8);
    spargel_assert(dirname_equal("D:\\hello\\world\\").length() == 14);

#else  // SPARGEL_IS_WINDOWS

    spargel_assert(dirname_equal("/", "/"));
    spargel_assert(dirname_equal("/hello", "/"));
    spargel_assert(dirname_equal("/hello/", "/"));
    spargel_assert(dirname_equal("/hello/world", "/hello"));
    spargel_assert(dirname_equal("/hello/world/", "/hello"));

#endif  // SPARGEL_IS_WINDOWS

    // relative
    spargel_assert(dirname_equal("", "."));
    spargel_assert(dirname_equal(".", "."));
    spargel_assert(dirname_equal("hello", "."));
    spargel_assert(dirname_equal("hello/", "."));
    spargel_assert(dirname_equal("hello/world", "hello"));
    spargel_assert(dirname_equal("hello/world/", "hello"));
    spargel_assert(dirname_equal("./hello", "."));
    spargel_assert(dirname_equal("./hello/", "."));
    spargel_assert(dirname_equal("./hello/world", "./hello"));
    spargel_assert(dirname_equal("./hello/world/", "./hello"));
}

void test_parsePath() {
    util::ParsedPath parsed;

    parsed = util::parsePath(base::string(""));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory == false);
    spargel_assert(parsed.components.count() == 0);

    parsed = util::parsePath(base::string("."));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory == false);
    spargel_assert(parsed.components.count() == 1);
    spargel_assert(parsed.components[0] == base::string("."));

    parsed = util::parsePath(base::string("./"));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory == true);
    spargel_assert(parsed.components.count() == 1);
    spargel_assert(parsed.components[0] == base::string("."));

    parsed = util::parsePath(base::string("hello"));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory == false);
    spargel_assert(parsed.components.count() == 1);
    spargel_assert(parsed.components[0] == base::string("hello"));

    parsed = util::parsePath(base::string("hello/"));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory = true);
    spargel_assert(parsed.components.count() == 1);
    spargel_assert(parsed.components[0] == base::string("hello"));

    parsed = util::parsePath(base::string("hello/world"));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory == false);
    spargel_assert(parsed.components.count() == 2);
    spargel_assert(parsed.components[0] == base::string("hello"));
    spargel_assert(parsed.components[1] == base::string("world"));

    parsed = util::parsePath(base::string("hello/world/"));
    spargel_assert(parsed.absolute == false);
    spargel_assert(parsed.directory = true);
    spargel_assert(parsed.components.count() == 2);
    spargel_assert(parsed.components[0] == base::string("hello"));
    spargel_assert(parsed.components[1] == base::string("world"));

    parsed = util::parsePath(base::string("/hello/world"));
    spargel_assert(parsed.absolute == true);
    spargel_assert(parsed.directory == false);
    spargel_assert(parsed.components.count() == 2);
    spargel_assert(parsed.components[0] == base::string("hello"));
    spargel_assert(parsed.components[1] == base::string("world"));

    parsed = util::parsePath(base::string("/hello/world/"));
    spargel_assert(parsed.absolute == true);
    spargel_assert(parsed.directory = true);
    spargel_assert(parsed.components.count() == 2);
    spargel_assert(parsed.components[0] == base::string("hello"));
    spargel_assert(parsed.components[1] == base::string("world"));
}

int main() {
    test_dirname();

    test_parsePath();

    return 0;
}
