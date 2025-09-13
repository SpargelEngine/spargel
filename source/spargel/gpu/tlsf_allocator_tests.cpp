#include "spargel/base/check.h"
#include "spargel/base/test.h"
#include "spargel/gpu/tlsf_allocator.h"

namespace spargel::gpu {
    namespace {
        void checkBinUp(usize size, u8 bin, u8 subbin) {
            auto result = TlsfBinner{}.binUp(size);
            if (result.bin_id != bin || result.subbin_id != subbin) {
                spargel_log_error("size: %zu, expected: (%d, %d) actual: (%d, %d)", size, bin,
                                  subbin, result.bin_id, result.subbin_id);
                spargel_panic_here();
            }
        }
        void checkBinDown(usize size, u8 bin, u8 subbin) {
            auto result = TlsfBinner{}.binDown(size);
            if (result.bin_id != bin || result.subbin_id != subbin) {
                spargel_log_error("size: %zu, expected: (%d, %d) actual: (%d, %d)", size, bin,
                                  subbin, result.bin_id, result.subbin_id);
                spargel_panic_here();
            }
        }

        TEST(TlsfBinner_BinUp) {
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
        TEST(TlsfBinner_BinDown) {
            // NOTE: This is special.
            // NOTE: Nothing goes to the subbin 0.
            checkBinDown(1, 0, 0);
            checkBinDown(2, 0, 0);
            checkBinDown(7, 0, 0);
            checkBinDown(8, 0, 1);
            checkBinDown(9, 0, 1);
            checkBinDown(15, 0, 1);
            checkBinDown(16, 0, 2);
            checkBinDown(17, 0, 2);
            checkBinDown(24, 0, 3);
            checkBinDown(25, 0, 3);
            checkBinDown(31, 0, 3);
            checkBinDown(32, 0, 4);
            checkBinDown(247, 0, 30);
            checkBinDown(248, 0, 31);
            checkBinDown(249, 0, 31);
            checkBinDown(255, 0, 31);
            checkBinDown(256, 1, 0);
        }
    }  // namespace
}  // namespace spargel::gpu
