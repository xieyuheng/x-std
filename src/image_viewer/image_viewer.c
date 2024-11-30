#include "index.h"

image_viewer_t *
image_viewer_new(const char *path) {
    image_viewer_t *self = allocate(sizeof(image_viewer_t));
    self->path = path;
    return self;
}

void
image_viewer_destroy(image_viewer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        image_viewer_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
image_viewer_open(image_viewer_t *self) {
    canvas_t *canvas = canvas_new(0x10 * 8, 0x10 * 8);
    canvas_window_t *canvas_window = canvas_window_new(canvas, 8);
    canvas_window->title = "image viewer";
    file_t *file = file_open_or_fail(self->path, "rb");
    uint8_t *bytes = file_read_bytes(file);
    canvas_draw_chr(canvas, 0, 0, bytes, 0x10, 0x10, 1);
    // canvas_draw_icn(canvas, 0, 0, bytes, 0x10, 0x10, 1);
    canvas_window_open(canvas_window);

    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);
}
