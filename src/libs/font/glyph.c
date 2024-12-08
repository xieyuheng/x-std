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

glyph_t *
glyph_new(code_point_t code_point, size_t width, size_t height) {
    glyph_t *self = new(glyph_t);
    self->code_point = code_point;

    assert(width == 8 || width == 16);
    self->width = width;

    assert(height == 16);
    self->height = height;

    self->bitmap = allocate(height * width / 8);
    return self;
}

void
glyph_destroy(glyph_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        glyph_t *self = *self_pointer;
        free(self->bitmap);
        free(self);
        *self_pointer = NULL;
    }
}
