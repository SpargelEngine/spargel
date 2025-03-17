#version 460

#define N 16

layout (local_size_x = N / 2) in;

layout (std430, set = 0, binding = 0) buffer Data {
    restrict uint data[];
} data;

shared uint local[N];

void compareAndSwap(uint i, uint j) {
    if (local[i] > local[j]) {
        uint tmp = local[i];
        local[i] = local[j];
        local[j] = tmp;
    }
}

void main() {
    uint id = gl_GlobalInvocationID.x;

    // Step 1. Read data. Each thread reads two value.
    local[id * 2] = data.data[id * 2];
    local[id * 2 + 1] = data.data[id * 2 + 1];

    // Step 2. Sort!
    for (uint h1 = 2; h1 <= N; h1 *= 2) {
        barrier();

        uint d1 = ((id * 2) / h1) * h1;
        compareAndSwap(d1 + (id % (h1 / 2)), d1 + (h1 - 1 - (id % (h1 / 2))));

        for (uint h2 = h1 / 2; h2 > 1; h2 /= 2) {
            barrier();

            uint d2 = ((id * 2) / h2) * h2;
            compareAndSwap(d2 + (id % (h2 / 2)), d2 + (id % (h2 / 2)) + (h2 / 2));
        }
    }

    //  Step 3. Write back.
    barrier();

    data.data[id * 2] = local[id * 2];
    data.data[id * 2 + 1] = local[id * 2 + 1];
}
