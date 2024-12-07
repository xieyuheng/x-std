#include "index.h"

editor_t *
editor_new(void) {
    editor_t *self = new(editor_t);
    canvas_t *canvas = canvas_new(0xa * TILE, 0xa * TILE, 0x8);
    canvas->state = self;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "bifer";
    self->canvas = canvas;
    return self;
}

void
editor_destroy(editor_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        editor_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        free(self);
        *self_pointer = NULL;
    }
}

static void on_frame(editor_t *self, canvas_t *canvas, uint64_t passed);

void
editor_open(editor_t *self) {
    self->canvas->on_frame = (on_frame_t *) on_frame;
    canvas_open(self->canvas);
}

void
editor_start(void) {
    editor_t *self = editor_new();
    editor_open(self);
    editor_destroy(&self);
}

void
on_frame(editor_t *self, canvas_t *canvas, uint64_t passed) {
    (void) self;
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);
}
