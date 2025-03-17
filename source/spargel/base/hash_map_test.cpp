#include <spargel/base/allocator.h>
#include <spargel/base/check.h>
#include <spargel/base/hash_map.h>
#include <spargel/base/string.h>
#include <spargel/base/test.h>

using namespace spargel::base;

TEST(HashMap_CopyConstructor) {
    HashMap<int, int> z1(default_allocator());
    z1.set(2, 100);

    auto z2(z1);
    spargel_check(z2.get(2) != nullptr);
    spargel_check(*z2.get(2) == 100);

    auto z3 = z2;
    spargel_check(z3.get(2) != nullptr);
    spargel_check(*z3.get(2) == 100);

    HashMap<string, string> z4(default_allocator());
    z4.set(string("name"), string("Alice"));

    auto z5(z4);
    spargel_check(z5.get(string("name")) != nullptr);
    spargel_check(*z5.get(string("name")) == string("Alice"));

    auto z6 = z5;
    spargel_check(z6.get(string("name")) != nullptr);
    spargel_check(*z6.get(string("name")) == string("Alice"));
}

TEST(HashMap_MoveConstructor) {
    HashMap<int, int> z1(default_allocator());
    z1.set(2, 100);

    auto z2(move(z1));
    spargel_check(z2.get(2) != nullptr);
    spargel_check(*z2.get(2) == 100);

    auto z3 = move(z2);
    spargel_check(z3.get(2) != nullptr);
    spargel_check(*z3.get(2) == 100);

    HashMap<string, string> z4(default_allocator());
    z4.set(string("name"), string("Alice"));

    auto z5(move(z4));
    spargel_check(z5.get(string("name")) != nullptr);
    spargel_check(*z5.get(string("name")) == string("Alice"));

    auto z6 = move(z5);
    spargel_check(z6.get(string("name")) != nullptr);
    spargel_check(*z6.get(string("name")) == string("Alice"));
}

TEST(HashMap_General) {
    HashMap<int, int> x(default_allocator());

    spargel_check(x.count() == 0);
    spargel_check(x.get(100) == nullptr);

    x.set(1, 2);

    spargel_check(x.count() == 1);

    spargel_check(x.get(1) != nullptr);
    spargel_check(x.get(2) == nullptr);
    spargel_check(*x.get(1) == 2);

    for (int i = 5; i < 100; i++) {
        x.set(i, i * i);
    }

    for (int i = 5; i < 100; i++) {
        spargel_check(x.get(i) != nullptr);
        spargel_check(*x.get(i) == i * i);
    }

    HashMap<string, string> y(default_allocator());

    spargel_check(y.count() == 0);
    spargel_check(y.get(string("name")) == nullptr);

    y.set(string("name"), string("Alice"));

    spargel_check(y.count() == 1);
    spargel_check(*y.get(string("name")) == string("Alice"));
}
