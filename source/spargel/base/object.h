#pragma once

#include <spargel/base/meta.h>
#include <spargel/base/types.h>

//
#include <new>  // placement new

namespace spargel::base {

    template <typename T, typename... Args>
    void construct_at(T* ptr, Args&&... args) {
        new (ptr) T(forward<Args>(args)...);
    }

    template <typename T>
    void destruct_at(T* ptr) {
        ptr->~T();
    }

    template <typename T>
    T* start_lifetime_as(void* ptr) {
        auto bytes = new (ptr) Byte[sizeof(T)];
        return reinterpret_cast<T*>(bytes);
    }

}  // namespace spargel::base
