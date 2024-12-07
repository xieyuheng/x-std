#include "index.h"

utf8_iter_t *
utf8_iter_new(const char *string) {
    utf8_iter_t *self = new(utf8_iter_t);
    self->cursor = 0;
    self->string = string;
    return self;
}

void
utf8_iter_destroy(utf8_iter_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        utf8_iter_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

code_point_t
utf8_iter_current(utf8_iter_t *self) {
    return utf8_code_point(self->string + self->cursor);
}
