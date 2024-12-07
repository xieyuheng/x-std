#include "index.h"

utf8_iter_t *
utf8_iter_new(const char *string) {
    utf8_iter_t *self = new(utf8_iter_t);
    self->cursor = 0;
    self->string = string;
    return self;
}
