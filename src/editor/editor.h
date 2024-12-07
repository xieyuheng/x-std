#pragma once

struct editor_t {
    canvas_t *canvas;
};

editor_t *editor_new(void);
void editor_destroy(editor_t **self_pointer);

void editor_open(editor_t *self);
void editor_start(void);
