#pragma once

struct font_viewer_t {
    canvas_t *canvas;
};

font_viewer_t *font_viewer_new(void);
void font_viewer_destroy(font_viewer_t **self_pointer);

void font_viewer_open(font_viewer_t *self);
void font_viewer_start(void);
