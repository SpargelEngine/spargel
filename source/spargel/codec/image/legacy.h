#pragma once

#include <spargel/base/types.h>

/**
 * todo:
 *  - bmp
 *  - png
 *  - openexr
 *  - ptex
 */

/* this is a hack */
struct color4 {
    u8 b;
    u8 g;
    u8 r;
    u8 a;
};

struct image {
    int width;
    int height;
    struct color4* pixels;
};

void destroy_image(struct image image);

enum decode_result {
    DECODE_SUCCESS,
    /* todo: better error codes */
    DECODE_FAILED,
};

/**
 * @brief ppm loader
 */
int load_ppm_image(char const* path, struct image* image);

void destroy_image(struct image const* image);
