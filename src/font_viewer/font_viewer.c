#include "index.h"

font_viewer_t *
font_viewer_new(void) {
    font_viewer_t *self = new(font_viewer_t);
    canvas_t *canvas = canvas_new(0xa * TILE, 0xa * TILE, 0x8);
    canvas->state = self;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "bifer";
    self->canvas = canvas;
    return self;
}

void
font_viewer_destroy(font_viewer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        font_viewer_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        free(self);
        *self_pointer = NULL;
    }
}

static void on_frame(font_viewer_t *self, canvas_t *canvas, uint64_t passed);

void
font_viewer_open(font_viewer_t *self) {
    self->canvas->on_frame = (on_frame_t *) on_frame;
    canvas_open(self->canvas);
}

void
font_viewer_start(void) {
    font_viewer_t *self = font_viewer_new();
    font_viewer_open(self);
    font_viewer_destroy(&self);
}

void
on_frame(font_viewer_t *self, canvas_t *canvas, uint64_t passed) {
    (void) self;
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);
}
