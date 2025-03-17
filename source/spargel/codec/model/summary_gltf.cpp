#include <spargel/codec/model/gltf.h>
#include <spargel/resource/directory.h>

/* libc */
#include <stdio.h>

using namespace spargel;
using namespace spargel::codec;
using namespace spargel::codec::model;

namespace {

    void dumpGlTF(const GlTF& gltf) {
        // asset
        auto& asset = gltf.asset;
        puts("asset:");
        printf("  version: \"%s\"\n", asset.version.data());
        if (asset.copyright.hasValue())
            printf("  copyright: \"%s\"\n", asset.copyright.value().data());
        if (asset.generator.hasValue())
            printf("  generator: \"%s\"\n", asset.generator.value().data());
        if (asset.minVersion.hasValue())
            printf("  minVersion: \"%s\"\n", asset.minVersion.value().data());

        if (gltf.accessors.hasValue()) printf("accessors: %zu\n", gltf.accessors.value().count());

        if (gltf.buffers.hasValue()) printf("buffers: %zu\n", gltf.buffers.value().count());

        if (gltf.bufferViews.hasValue())
            printf("bufferViews: %zu\n", gltf.bufferViews.value().count());

        if (gltf.nodes.hasValue()) printf("nodes: %zu\n", gltf.nodes.value().count());

        if (gltf.scenes.hasValue()) printf("scenes: %zu\n", gltf.scenes.value().count());

        if (gltf.scene.hasValue()) printf("scene: %d\n", gltf.scene.value());
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

    auto result = parseGlTF((char*)resource->mapData(), resource->size());
    if (result.isLeft()) {
        dumpGlTF(base::move(result.left()));
        putchar('\n');
    } else {
        fprintf(stderr, "Failed to parse glTF: %s\n", result.right().message().data());
    }

    return 0;
}
