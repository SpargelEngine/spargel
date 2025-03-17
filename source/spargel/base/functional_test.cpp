#include <spargel/base/check.h>
#include <spargel/base/functional.h>
#include <spargel/base/test.h>

using namespace spargel::base;

constexpr double f(int a, double b, int c) { return a + b + c; }

static_assert(curry(f, 1)(2.5, 3) == 6.5);

struct A {
    int a;
    double b;

    A(int a, double b) : a(a), b(b) {}
};

TEST(Constructor) {
    {
        Constructor<int(int)> ctor;
        auto a = ctor(123);
        spargel_check(a == 123);
    }
    {
        Constructor<A(int, double)> ctor;
        auto a = ctor(123, 456.789);
        spargel_check(a.a == 123);
        spargel_check(a.b == 456.789);
    }
}

TEST(Curry_Basic) {
    spargel_check(curry(f, 1)(2.5, 3) == 6.5);

    auto log = curry(printf, "LOG: %s\n");
    log("Hello!");
}

TEST(Curry_Lambda) {
    int a = 1;
    auto g = [&a](int b, int c, int d) { return a + b + c + d; };
    spargel_check(curry(g, 2)(3, 4) == 10);
}

TEST(Curry_Arg_Reference) {
    auto g = [](int& a, int b) { a = b + 1; };

    int a = 1;
    auto g2 = curry(g, a);
    g2(3);
    spargel_check(a == 3 + 1);
}

TEST(Constructor_Curry) {
    {
        auto a = curry(Constructor<A(int, double)>(), 123)(456.789);
        spargel_check(a.a == 123);
        spargel_check(a.b == 456.789);
    }
}
