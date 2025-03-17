#pragma once

#include <spargel/resource/resource.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>

namespace spargel::entry {

    struct simple_entry_data {
        base::unique_ptr<ui::Platform> platform;
        base::unique_ptr<ui::Window> window;
        base::unique_ptr<resource::ResourceManager> resource_manager;
    };

    int simple_entry(entry::simple_entry_data* entry_data);

}  // namespace spargel::entry
