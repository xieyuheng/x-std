#pragma once

glyph_t *glyph_new(code_point_t code_point, size_t width, size_t height);
void glyph_destroy(glyph_t **self_pointer);

code_point_t glyph_code_point(const glyph_t *self);
size_t glyph_width(const glyph_t *self);
size_t glyph_height(const glyph_t *self);
