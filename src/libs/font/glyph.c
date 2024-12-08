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

code_point_t
glyph_code_point(const glyph_t *self) {
    return self->code_point;
}

size_t
glyph_width(const glyph_t *self) {
    return self->width;
}

size_t
glyph_height(const glyph_t *self) {
    return self->height;
}

bool
glyph_get(const glyph_t *self, size_t x, size_t y) {
    if (self->width == 8) {
        uint8_t byte = self->bitmap[y];
        return (byte >> x) & 0x1;
    }

    assert(self->width == 16);
    if (x < 8) {
        uint8_t byte = self->bitmap[y * 2];
        return (byte >> x) & 0x1;
    } else {
        uint8_t byte = self->bitmap[y * 2 + 1];
        return (byte >> (x - 8)) & 0x1;
    }
}

glyph_t *
glyph_parse_hex(const char* string) {
    int colon_index = string_find_index(string, ':');
    assert(colon_index != -1);

    code_point_t code_point = string_parse_hex(string);
    string += colon_index;

    int newline_index = string_find_index(string, '\n');
    if (newline_index == -1) {
        newline_index = string_find_index(string, '\0');
        assert(newline_index != -1);
    }

    size_t width = newline_index / 2; // two hex chars is one byte.
    size_t height = 16;
    glyph_t *glyph = glyph_new(code_point, width, height);
    // for () {
    //     glyph->bitmap = ;
    // }

    return glyph;
}
