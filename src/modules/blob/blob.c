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
