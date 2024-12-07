#include "index.h"

text_t *
text_new(size_t length) {
    text_t *self = new(text_t);
    self->length = length;
    self->code_points = allocate_many(length, sizeof(text_t));
    return self;
}
