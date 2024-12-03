#include "index.h"

image_viewer_t *
image_viewer_new(const char *path) {
    image_viewer_t *self = allocate(sizeof(image_viewer_t));
    self->path = path;
    self->blending = 1;
    self->scale = 8;
    self->is_changed = true;
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

static void
on_key(canvas_window_t *window, image_viewer_t *self, const char *key_name, bool is_release) {
    (void) window;

    if (is_release) {
        if (string_equal_mod_case(key_name, "tab")) {
            self->blending = (self->blending + 1) % 16;
            self->is_changed = true;
        }
    }
}

static void
on_frame(canvas_window_t *window, image_viewer_t *self, uint64_t expirations) {
    (void) expirations;

    if (!self->is_changed) return;

    size_t width = image_width_from_path(self->path);
    size_t height = image_height_from_path(self->path);
    printf("[image_viewer/on_frame] width:  0x%lxti\n", width);
    printf("[image_viewer/on_frame] height: 0x%lxti\n", height);
    printf("[image_viewer/on_frame] blending: 0x%x\n", self->blending);

    file_t *file = file_open_or_fail(self->path, "rb");
    uint8_t *bytes = file_read_bytes(file);

    if (string_ends_with(self->path, ".icn"))
        canvas_draw_icn(window->canvas, 0, 0, bytes, width, height, self->blending);

    if (string_ends_with(self->path, ".chr"))
        canvas_draw_chr(window->canvas, 0, 0, bytes, width, height, self->blending);

    self->is_changed = false;
}

void
image_viewer_open(image_viewer_t *self) {
    size_t width = image_width_from_path(self->path);
    size_t height = image_height_from_path(self->path);
    printf("[image_viewer_open] width:  0x%lxti\n", width);
    printf("[image_viewer_open] height: 0x%lxti\n", height);

    canvas_t *canvas = canvas_new(width * TILE, height * TILE, self->scale);
    canvas->window->title = self->path;
    canvas->window->state = self;
    canvas->window->on_key = (on_key_t *) on_key;
    canvas->window->on_frame = (on_frame_t *) on_frame;

    canvas_open(canvas);

    canvas_destroy(&canvas);
}
