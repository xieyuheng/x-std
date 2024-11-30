#pragma once

struct image_viewer_t {
    const char *path;
    const char *window_title;
};

image_viewer_t *image_viewer_new(const char *path);
void image_viewer_destroy(image_viewer_t **self_pointer);
