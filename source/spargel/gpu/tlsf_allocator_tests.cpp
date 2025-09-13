#include "spargel/base/check.h"
#include "spargel/base/test.h"
#include "spargel/gpu/tlsf_allocator.h"

namespace spargel::gpu {
    namespace {
        void checkBinUp(usize size, u8 bin, u8 subbin) {
            auto result = TlsfBinner{}.binUp(size);
            if (result.bin_id != bin || result.subbin_id != subbin) {
                spargel_log_error("expected: (%d, %d) actual: (%d, %d)", bin, subbin,
                                  result.bin_id, result.subbin_id);
                spargel_panic_here();
            }
        }

        TEST(TlsfBinner_Basic) {
            // NOTE: This is special.
            // NOTE: Nothing goes to the subbin 0.
            checkBinUp(1, 0, 1);
            checkBinUp(2, 0, 1);
            checkBinUp(7, 0, 1);
            checkBinUp(8, 0, 1);
            checkBinUp(9, 0, 2);
            checkBinUp(15, 0, 2);
            checkBinUp(16, 0, 2);
            checkBinUp(17, 0, 3);
            checkBinUp(24, 0, 3);
            checkBinUp(25, 0, 4);
            checkBinUp(31, 0, 4);
            checkBinUp(32, 0, 4);
            checkBinUp(247, 0, 31);
            checkBinUp(248, 0, 31);
            checkBinUp(249, 1, 0);
            checkBinUp(255, 1, 0);
            checkBinUp(256, 1, 0);
        }
    }  // namespace
}  // namespace spargel::gpu
