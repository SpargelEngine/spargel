#include <spargel/base/logging.h>
#include <spargel/base/string.h>
#include <spargel/resource/directory.h>
#include <spargel/resource/overlay.h>

using namespace spargel;

// libc
#include <stdio.h>

int main() {
    base::vector<base::unique_ptr<resource::ResourceManager>> managers;
    managers.push(resource::makeRelativeManager(base::string("resources2")));
    managers.push(resource::makeRelativeManager(base::string("resources")));
    auto manager = resource::ResourceManagerOverlay(base::move(managers));

    base::string_view path1 = "dir/abc.txt";

    auto resource1 = manager.open(resource::ResourceId(path1));
    if (!resource1.hasValue()) {
        spargel_log_error("Cannot open resource \"%s\"", path1.data());
        return 1;
    }

    spargel_log_info("%s (%zu): ", path1.data(), resource1.value()->size());
    char* data1 = (char*)resource1.value()->mapData();
    for (usize i = 0; i < resource1.value()->size(); i++) putchar(data1[i]);
    putchar('\n');

    base::string_view path2 = "hello.txt";

    auto resource2 = manager.open(resource::ResourceId(path2));
    if (!resource2.hasValue()) {
        spargel_log_error("Cannot open resource \"%s\"", path2.data());
        return 1;
    }

    spargel_log_info("%s (%zu): ", path2.data(), resource2.value()->size());
    char* data2 = (char*)resource2.value()->mapData();
    for (usize i = 0; i < resource2.value()->size(); i++) putchar(data2[i]);
    putchar('\n');

    return 0;
}
