#include "index.h"

struct font_t {
    glyph_t **glyphs;
};

font_t *
font_new(void) {
    font_t *self = new(font_t);
    // length is one more than the max.
    self->glyphs = allocate_pointers(MAX_CODE_POINT + 1);
    return self;
}

void
font_destroy(font_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        font_t *self = *self_pointer;
        free(self->glyphs);
        free(self);
        *self_pointer = NULL;
    }
}

glyph_t *
font_get(font_t *self, code_point_t code_point) {
    assert(code_point <= MAX_CODE_POINT);
    return self->glyphs[code_point];
}

void
font_put(font_t *self, glyph_t *glyph) {
    self->glyphs[glyph_code_point(glyph)] = glyph;
}

font_t *
font_load_hex_file(file_t *file) {
    font_t *font = font_new();
    char *string = file_read_string(file);

    // char *line = string;
    // while (line) {
    //     font_put(glyph_parse_hex(line));
    //     line = string_next_line(line);
    // }

    free(string);
    return font;
}
