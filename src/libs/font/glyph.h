#pragma once

glyph_t *glyph_new(code_point_t code_point, size_t width, size_t height);
void glyph_destroy(glyph_t **self_pointer);
