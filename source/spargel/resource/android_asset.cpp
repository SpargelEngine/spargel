#include <spargel/resource/android_asset.h>

namespace spargel::resource {

    class ResourceAndroidAsset : public Resource {
        friend class ResourceManagerAndroidAsset;

    public:
        ~ResourceAndroidAsset() override;

        usize size() override;

        void getData(void* buf) override;

        AAsset* _asset;

        explicit ResourceAndroidAsset(AAsset* asset) : _asset(asset) {}
    };

    ResourceAndroidAsset::~ResourceAndroidAsset() { AAsset_close(_asset); }

    usize ResourceAndroidAsset::size() { return AAsset_getLength(_asset); }

    void ResourceAndroidAsset::getData(void* buf) { AAsset_read(_asset, buf, size()); }

    base::Optional<base::unique_ptr<Resource>> ResourceManagerAndroidAsset::open(
        const resource::ResourceId& id) {
        AAsset* asset = AAssetManager_open(_asset_manager, id.path().data(), AASSET_MODE_BUFFER);
        return asset ? base::makeOptional<base::unique_ptr<ResourceAndroidAsset>>(
                           base::make_unique<ResourceAndroidAsset>(asset))
                     : base::nullopt;
    }
}  // namespace spargel::resource
