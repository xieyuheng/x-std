#include "index.h"

#define MAX_CODE_POINT 0x110000

struct font_t {
    glyph_t *glyphs;
};

font_t *
font_new(void) {
    font_t *self = new(font_t);
    self->glyphs = allocate_pointers(MAX_CODE_POINT);
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

font_t *
font_load_hex_file(file_t *file) {
    font_t *font = font_new();
    char *string = file_read_string(file);

    // char *line = string;
    // while (line) {
    //     font_put_glyph(glyph_parse_hex(line));
    //     line = string_next_line(line);
    // }

    free(string);
    return font;
}
