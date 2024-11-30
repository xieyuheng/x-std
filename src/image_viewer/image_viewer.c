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
