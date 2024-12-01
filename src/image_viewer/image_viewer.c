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

static uint8_t parse_image_width(const char *path) {
    size_t length = strlen(path);
    const char *width_start = path + (length - 9);
    return strtol(width_start, NULL, 16);
}

static uint8_t parse_image_height(const char *path) {
    size_t length = strlen(path);
    const char *height_start = path + (length - 6);
    return strtol(height_start, NULL, 16);
}

static void on_key(
    canvas_window_t *canvas_window,
    image_viewer_t *self,
    const char *key_name,
    bool is_release);

void
image_viewer_open(image_viewer_t *self, const char *path) {
    size_t width = parse_image_width(path);
    size_t height = parse_image_height(path);
    printf("[image_viewer_open] width: 0x%lxti, height: 0x%lxti\n", width, height);

    canvas_t *canvas = canvas_new(width, height);
    canvas_window_t *canvas_window = canvas_window_new(canvas, self->scale);
    canvas_window->title = path;
    canvas_window->state = self;
    canvas_window->on_key = (on_key_t *) on_key;

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

void on_key(
    canvas_window_t *canvas_window,
    image_viewer_t *self,
    const char *key_name,
    bool is_release
) {
    (void) canvas_window;

    if (is_release) {
        if (string_equal(key_name, "Tab")) {
            self->blending = (self->blending + 1) % 16;
        }
    }
}
