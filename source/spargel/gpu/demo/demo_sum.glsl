#version 460

// compute the sum of two arrays

layout (local_size_x = 64) in;
layout (set = 0, binding = 0) uniform Control {
    // length of the arrays
    uint count;
} control;
layout (std430, set = 0, binding = 1) buffer In1 {
    readonly restrict float data[];
} in1;
layout (std430, set = 0, binding = 2) buffer In2 {
    readonly restrict float data[];
} in2;
layout (std430, set = 0, binding = 3) buffer Result {
    writeonly restrict float data[];
} result;

void main() {
    uint i = gl_GlobalInvocationID.x;
    if (i < control.count) {
        result.data[i] = in1.data[i] + in2.data[i];
    }
}
