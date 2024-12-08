#include "index.h"

// width and height are measured by pixel,
// currently only supported width is 8 and 16,
// only supported height is 16.

struct glyph_t {
    code_point_t code_point;
    size_t width;
    size_t height;
    uint8_t *bitmap;
};
