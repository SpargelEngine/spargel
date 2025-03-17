#include <spargel/base/string.h>
#include <spargel/entry/simple.h>
#include <spargel/resource/directory.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>

using namespace spargel;

int main() {
    entry::simple_entry_data data;
    data.platform = ui::makePlatform();
    data.window = data.platform->makeWindow(500, 500);
    data.resource_manager = resource::makeRelativeManager(base::string("resources"));

    return entry::simple_entry(&data);
}
