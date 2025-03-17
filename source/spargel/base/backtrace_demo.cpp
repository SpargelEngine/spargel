#include <spargel/base/backtrace.h>

void foo() { spargel::base::PrintBacktrace(); }

int main() {
    foo();
    return 0;
}
