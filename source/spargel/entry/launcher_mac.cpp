#include <spargel/base/logging.h>
#include <spargel/entry/component.h>
#include <spargel/entry/launch_data.h>
#include <spargel/ui/platform.h>

// platform
#include <dlfcn.h>

using namespace spargel;

int main(int argc, char* argv[]) {
    spargel_log_info("launcher started");
    if (argc < 2) {
        spargel_log_error("missing component");
        return 1;
    }
    char* path = argv[1];
    spargel_log_info("loading component <<%s>>", path);

    auto lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    auto maker = reinterpret_cast<entry::component* (*)(entry::launch_data*)>(
        dlsym(lib, "_spargel_make_component"));

    entry::launch_data data;
    auto platform = ui::makePlatform();
    data.platform = platform.get();

    auto component = maker(&data);
    component->on_load();

    platform->startLoop();

    dlclose(lib);
    return 0;
}
