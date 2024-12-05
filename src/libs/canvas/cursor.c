#include "index.h"

cursor_t *
cursor_new(size_t x, size_t y) {
    cursor_t *self = new(cursor_t);
    self->x = x;
    self->y = y;
    return self;
}
