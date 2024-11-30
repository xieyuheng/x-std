#include "index.h"

image_viewer_t *
image_viewer_new(void) {
    image_viewer_t *self = allocate(sizeof(image_viewer_t));
    self->blending = 1;
    self->scale = 8;
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
image_viewer_open(image_viewer_t *self, const char *path) {
    size_t width = 0x10;
    size_t height = 0x10;
    canvas_t *canvas = canvas_new(width * self->scale, height * self->scale);
    canvas_window_t *canvas_window = canvas_window_new(canvas, self->scale);
    canvas_window->title = "image viewer";
    file_t *file = file_open_or_fail(path, "rb");
    uint8_t *bytes = file_read_bytes(file);
    if (string_ends_with(path, ".icn")) {
        canvas_draw_icn(canvas, 0, 0, bytes, width, height, self->blending);
    }

    if (string_ends_with(path, ".chr")) {
        canvas_draw_chr(canvas, 0, 0, bytes, width, height, self->blending);
    }

    canvas_window_open(canvas_window);
    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);
}
