#include "index.h"

text_t *
text_new(size_t length) {
    text_t *self = new(text_t);
    self->length = length;
    self->code_points = allocate_many(length, sizeof(text_t));
    return self;
}

void
text_destroy(text_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        text_t *self = *self_pointer;
        free(self->code_points);
        free(self);
        *self_pointer = NULL;
    }
}

text_t *
text_from_string(const char *string) {
    size_t length = utf8_string_length(string);
    text_t *text = text_new(length);

    utf8_iter_t *iter = utf8_iter_new(string);
    code_point_t code_point = utf8_iter_start(iter);
    size_t index = 0;
    while (code_point) {
        text->code_points[index] = code_point;
        code_point = utf8_iter_next(iter);
        index++;
    }

    return text;
}
