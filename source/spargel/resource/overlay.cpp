#include <spargel/resource/overlay.h>

namespace spargel::resource {

    bool ResourceManagerOverlay::has(const ResourceId& id) {
        for (auto& manager : _sub_managers) {
            if (manager->has(id)) return true;
        }
        return false;
    }

    base::Optional<base::unique_ptr<Resource>> ResourceManagerOverlay::open(const ResourceId& id) {
        for (auto& manager : _sub_managers) {
            if (manager->has(id)) {
                auto resource = manager->open(id);
                if (resource.hasValue()) return resource;
            }
        }
        return base::nullopt;
    }

}  // namespace spargel::resource
