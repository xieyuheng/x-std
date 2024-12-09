#include "index.h"

// with an extra ending '\0' to be viewed as string.

struct blob_t {
    size_t length;
    uint8_t *bytes;
};

blob_t *
blob_new(size_t length) {
    blob_t *self = new(blob_t);
    self->length = length;
    self->bytes = allocate(length + 1);
    return self;
}

void
blob_destroy(blob_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        blob_t *self = *self_pointer;
        free(self->bytes);
        free(self);
        *self_pointer = NULL;
    }
}
