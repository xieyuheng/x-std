#include "index.h"

struct glyph_iter_t {
    const font_t *font;
    code_point_t cursor;
};

glyph_iter_t *
glyph_iter_new(const font_t *font) {
    glyph_iter_t *self = new(glyph_iter_t);
    self->font = font;
    self->cursor = 0;
    return self;
}
