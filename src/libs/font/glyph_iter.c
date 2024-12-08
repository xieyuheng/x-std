#include "index.h"
font_nex
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

void
glyph_iter_destroy(glyph_iter_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        glyph_iter_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

glyph_t *
glyph_iter_start(glyph_iter_t *self) {
    self->cursor = 0;
    while (self->cursor <= MAX_CODE_POINT) {
        glyph_t *glyph = font_get(self->font, self->cursor);
        if (glyph) return glyph;
        self->cursor++;
    }

    return NULL;
}

glyph_t *
glyph_iter_next(glyph_iter_t *self) {
    self->cursor++;
    while (self->cursor <= MAX_CODE_POINT) {
        glyph_t *glyph = font_get(self->font, self->cursor);
        if (glyph) return glyph;
        self->cursor++;
    }

    return NULL;
}
