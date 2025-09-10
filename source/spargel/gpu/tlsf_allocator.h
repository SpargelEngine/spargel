#pragma once

#include "spargel/base/types.h"

namespace spargel::gpu {
    // The TLSF Allocator
    //
    // One instance manages a sequence of memory blocks, which are binned into a two levels.
    //
    // The number of (first level) bins is `bin_count`. Each bin contains `subbin_count` many
    // (second level) sub-bins. Every sub-bin contains a sequence of memory blocks, organized as a
    // free-list.
    //
    // Suppose the i-th (first level) bin is for memory blocks with size in [a, b).
    // Let delta be ceil((b - a) / subbin_count).
    // Then the j-th sub-bin is for blocks with size in [a + j * delta, a + (j + 1) * delta).
    //
    // We maintain two lookup structures:
    // - The first one is a bitset indicating whether each bin contains free memory blocks.
    // - The second one is a bitset for every bin, indicating which sub-bins contains free blocks.
    //
    // It remains to have a good choice of (first level) bins. A common approach is to associate
    // [2^i, 2^(i+1)) with the i-th bin. Zero-sized allocations are special handled. However, this
    // is not ideal for small sized bins.
    //
    // Therefore, we use the following ranges:
    // - 0-th bin: [2^0, 2^linear_bits)
    // - 1-th bin: [2^linear_bits, 2^(linear_bits + 1))
    // - 2-th bin: ...
    //
    // Then delta for sub-bins in the 0-th bin is (2^linear_bits - 1) / subbin_count, which is
    // about 3.9.
    //
    // Note: We would like 2^linear_bits to be divisible by subbin_count. So we take subbin_count to
    // be a power of 2. Moreover, we require that subbin_count <= 2^(linear_bits - 2) so that delta
    // >= 4.
    //
    //
    // size   | [2^0, 2^8) | [2^8, 2^9) | [2^9, 2^10) | ...
    // bin_id |     0      |      1     |       2     | ...
    //
    class TlsfAllocator {
        static constexpr u8 linear_bits = 8;
        static constexpr u8 subbin_bits = 5;
        static constexpr u8 subbin_count = 1 << subbin_bits;

    public:
        TlsfAllocator() = default;

    private:
        struct BinResult {
            u8 bin_id;
            u8 subbin_id;
        };
    };

}  // namespace spargel::gpu

// This is the allocator for device memory.
//
// The maximal memory allocation count (maxMemoryAllocationCount) returned by Vulkan drivers is
// still 4096 on half of the devices. So we should have few allocations of large device memory
// blocks, and then suballocate from these blocks. It's then our task to handle memory
// fragmentation.
//
// Two algorithms:
// - Bump allocator.
// - TLSF (two-level seggregated fit) allocator.
//
