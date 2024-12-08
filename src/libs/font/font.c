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
