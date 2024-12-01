#pragma once

struct image_viewer_t {
    const char *window_title;
    const char *path;
    uint8_t blending;
    size_t scale;
    bool is_changed;
};

image_viewer_t *image_viewer_new(const char *path);
void image_viewer_destroy(image_viewer_t **self_pointer);

void image_viewer_open(image_viewer_t *self);
