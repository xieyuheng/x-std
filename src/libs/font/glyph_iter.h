#pragma once

glyph_iter_t *glyph_iter_new(const font_t *font);
void glyph_iter_new(glyph_iter_t **self_pointer);

glyph_t *glyph_iter_start(glyph_iter_t *self);
glyph_t *glyph_iter_next(glyph_iter_t *self);
