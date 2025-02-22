
#include <spargel/base/assert.h>
#include <spargel/base/const.h>
#include <spargel/base/logging.h>
#include <spargel/base/platform.h>
#include <spargel/resource/directory.h>
#include <spargel/util/path.h>

// libc
#include <string.h>

#if SPARGEL_FILE_MMAP

#if SPARGEL_IS_POSIX
// POSIX
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif SPARGEL_IS_WINDOWS
#include <windows.h>
#endif

#else  // SPARGEL_FILE_MMAP

// libc
#include <stdio.h>

#endif  // SPARGEL_FILE_MMAP

namespace spargel::resource {

#if SPARGEL_FILE_MMAP

    ResourceDirectory::~ResourceDirectory() {
        if (_mapped) {
            _unmap(_mapped, _size);
        }
#if SPARGEL_IS_POSIX
        ::close(_fd);
#elif SPARGEL_IS_WINDOWS
        if (_mapping_handle) {
            CloseHandle(_mapping_handle);
        }
        CloseHandle(_file_handle);
#else
#error unimplemented
#endif  // SPARGEL_IS_POSIX
    }

    void ResourceDirectory::getData(void* buf) {
        if (!_mapped) {
            _mapped = _map();
        }
        memcpy(buf, _mapped, _size);
    }

    void* ResourceDirectory::mapData() {
        if (!_mapped) {
            _mapped = _map();
        }
        return _mapped;
    }

#if SPARGEL_IS_POSIX

    void* ResourceDirectory::_map() { return mmap(nullptr, _size, PROT_READ, MAP_PRIVATE, _fd, 0); }

    void ResourceDirectory::_unmap(void* ptr, usize size) { munmap(ptr, size); }

    ResourceDirectory* ResourceManagerDirectory::open(const ResourceId& id) {
        base::string real_path = _real_path(id);
        int fd = ::open(real_path.data(), O_RDONLY);
        if (fd < 0) {
            spargel_log_error("requested resource \"%s:%s\" not found", id.ns().data(),
                              id.path().data());
            return nullptr;
        }
        struct stat sb;
        if (fstat(fd, &sb) < 0) {
            ::close(fd);
            return nullptr;
        }

        return new ResourceDirectory(sb.st_size, fd);
    }

#elif SPARGEL_IS_WINDOWS

    void* ResourceDirectory::_map() {
        if (!_mapping_handle) {
            if (_file_handle == INVALID_HANDLE_VALUE) {
                spargel_log_error("invalid file handle");
                return nullptr;
            }
            _mapping_handle = CreateFileMappingA(_file_handle, nullptr, PAGE_READONLY,
                                                 HIWORD(_size), LOWORD(_size), nullptr);
            if (!_mapping_handle) {
                spargel_log_error("cannot create file mapping");
                return nullptr;
            }
        }
        return MapViewOfFile(_mapping_handle, FILE_MAP_READ, 0, 0, _size);
    }

    void ResourceDirectory::_unmap(void* ptr, usize size) { UnmapViewOfFile(ptr); }

    ResourceDirectory* ResourceManagerDirectory::open(const ResourceId& id) {
        base::string real_path = _real_path(id);
        HANDLE file_handle = CreateFileA(real_path.data(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
                                         FILE_ATTRIBUTE_READONLY, nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            spargel_log_error("requested resource \"%s:%s\" not found", id.ns().data(),
                              id.path().data());
            return nullptr;
        }

        LARGE_INTEGER size;
        if (!GetFileSizeEx(file_handle, &size)) {
            spargel_log_error("cannot get the size of resource \"%s:%s\"", id.ns().data(),
                              id.path().data());
            CloseHandle(file_handle);
            return nullptr;
        }

        return new ResourceDirectory(size.QuadPart, file_handle);
    }

#else
#error unimplemented
#endif  // SPARGEL_IS_POSIX

#else   // SPARGEL_FILE_MMAP

    ResourceDirectory::~ResourceDirectory() { fclose(_fp); }

    void ResourceDirectory::getData(void* buf) {
        fseek(_fp, 0, SEEK_SET);
        fread(buf, _size, 1, _fp);
    }

    void* ResourceDirectory::mapData() { return Resource::mapData(); }

    ResourceDirectory* ResourceManagerDirectory::open(const ResourceId& id) {
        base::string real_path = _real_path(id);
        FILE* fp = fopen(real_path.data(), "rb");
        if (!fp) {
            return nullptr;
        }
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        return new ResourceDirectory(size, fp);
    }
#endif  // SPARGEL_FILE_MMAP

    base::string ResourceManagerDirectory::_real_path(const ResourceId& id) {
        base::string root = _root_path.length() == 0 ? base::string(".") : _root_path;
        return root + PATH_SPLIT + id.path();
    }

    base::unique_ptr<ResourceManagerDirectory> makeRelativeManager() {
        base::string root_path =
            util::dirname(base::get_executable_path()) + PATH_SPLIT + base::string("resources");
        return base::make_unique<ResourceManagerDirectory>(root_path.view());
    }

}  // namespace spargel::resource
