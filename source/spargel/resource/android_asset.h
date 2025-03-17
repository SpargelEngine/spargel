#pragma once

#include <spargel/base/types.h>
#include <spargel/resource/resource.h>

// Android
#include <android/asset_manager.h>

namespace spargel::resource {

    class ResourceManagerAndroidAsset : public ResourceManager {
    public:
        explicit ResourceManagerAndroidAsset(AAssetManager* asset_manager)
            : _asset_manager(asset_manager) {}

        base::Optional<base::unique_ptr<Resource>> open(const ResourceId& id) override;

    private:
        AAssetManager* _asset_manager;
    };

}  // namespace spargel::resource
