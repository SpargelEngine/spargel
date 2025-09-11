#include "spargel/base/check.h"
#include "spargel/base/test.h"
#include "spargel/gpu/tlsf_allocator.h"

namespace spargel::gpu {
    namespace {
        void checkBin(TlsfBinner::BinResult result, u8 bin, u8 subbin) {
            spargel_check(result.bin_id == bin);
            spargel_check(result.subbin_id == subbin);
        }

        TEST(TlsfBinner_Basic) {
            TlsfBinner b;
            // NOTE: This is special.
            checkBin(b.binUp(1), 0, 1);
            checkBin(b.binUp(2), 0, 1);
            checkBin(b.binUp(7), 0, 1);
            checkBin(b.binUp(8), 0, 1);
            checkBin(b.binUp(9), 0, 2);
        }
    }  // namespace
}  // namespace spargel::gpu
