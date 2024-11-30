#pragma once

struct image_viewer_t {
    const char *window_title;
    uint8_t blending;
    size_t scale;
};

image_viewer_t *image_viewer_new(void);
void image_viewer_destroy(image_viewer_t **self_pointer);

void image_viewer_open(image_viewer_t *self, const char *path);
