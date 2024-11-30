#include "index.h"

image_viewer_t *
image_viewer_new(const char *path) {
    image_viewer_t *self = allocate(sizeof(image_viewer_t));
    self->path = path;
    return self;
}
