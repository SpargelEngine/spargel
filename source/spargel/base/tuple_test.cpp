#include <spargel/base/check.h>
#include <spargel/base/test.h>
#include <spargel/base/tuple.h>

using namespace spargel;

TEST(Tuple_Basic) {
    base::Tuple<int, int, bool, double> x;
    x.get<0>() = 1;
    spargel_check(x.get<0>() == 1);
    x.get<1>() = 2;
    spargel_check(x.get<0>() == 1);
    spargel_check(x.get<1>() == 2);
}
