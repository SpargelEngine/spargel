#pragma once

#include <spargel/base/optional.h>
#include <spargel/base/span.h>
#include <spargel/base/string.h>
#include <spargel/base/string_view.h>
#include <spargel/base/types.h>
#include <spargel/base/unique_ptr.h>

#include <cstddef>

namespace spargel::resource {

    class ResourceId {
    public:
        static constexpr base::string_view default_namespace = "core";

        ResourceId(const base::string& ns, const base::string& path)
            : _namespace(ns), _path(path) {}
        ResourceId(const base::string& path) : ResourceId(default_namespace, path) {}
        ResourceId(base::string_view ns, base::string_view path) : _namespace(ns), _path(path) {}
        ResourceId(base::string_view path) : ResourceId(default_namespace, path) {}

        const base::string& ns() const { return _namespace; }
        const base::string& path() const { return _path; }

    private:
        base::string _namespace;
        base::string _path;
    };

    class Resource;

    class ResourceManager {
    public:
        virtual ~ResourceManager() = default;

        virtual bool has(const ResourceId& id) = 0;

        virtual base::Optional<base::unique_ptr<Resource>> open(const ResourceId& id) = 0;
    };

    /*
     * This represents native resource handle class.
     * It can not be copied.
     */
    class Resource {
    public:
        Resource() : _mapped(nullptr), _mapped_size(0) {}

        Resource(Resource&) = delete;

        virtual ~Resource();

        virtual usize size() = 0;

        virtual void getData(void* buf) = 0;

        virtual void* mapData();

        base::span<u8> getSpan() { return base::make_span<u8>(size(), (u8*)mapData()); }

    private:
        void* _mapped;
        size_t _mapped_size;
    };

    // The most trivial example
    class ResourceManagerEmpty final : public ResourceManager {
    public:
        bool has(const ResourceId& id) override { return false; }

        base::Optional<base::unique_ptr<Resource>> open(const ResourceId& id) override {
            return base::nullopt;
        }
    };
}  // namespace spargel::resource
