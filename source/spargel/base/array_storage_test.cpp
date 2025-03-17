#include <spargel/base/allocator.h>
#include <spargel/base/array_storage.h>
#include <spargel/base/check.h>
#include <spargel/base/meta.h>
#include <spargel/base/test.h>

using namespace spargel::base;

TEST(ArrayStorage_DefaultConstructor) {
    ArrayStorage<int> y(nullptr);
    spargel_check(y.getCount() == 0);
    spargel_check(y.getAllocator() == nullptr);
}

TEST(ArrayStorage_ConstructByCapacity) {
    ArrayStorage<int> x(10, default_allocator());
    spargel_check(x.getCount() == 10);
    spargel_check(x.getAllocator() == default_allocator());
}

TEST(ArrayStorage_MoveConstructor) {
    ArrayStorage<int> x(10, default_allocator());
    ArrayStorage<int> z(move(x));
    spargel_check(x.getCount() == 0);  // NOLINT(clang-analyzer-cplusplus.Move)
    spargel_check(z.getCount() == 10);
    spargel_check(z.getAllocator() == default_allocator());
}
