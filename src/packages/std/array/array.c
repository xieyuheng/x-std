#include "index.h"

array_t *
array_new(size_t size) {
    array_t *self = new(array_t);
    self->size = size;
    self->grow_step = size;
    self->cursor = 0;
    self->values = allocate_pointers(size);
    return self;
}

void
array_purge(array_t *self) {
    assert(self);

    if (self->destroy_fn) {
        for (size_t i = 0; i < self->size; i++) {
            void *value = array_get(self, i);
            if (value) {
                self->destroy_fn(&value);
                array_set(self, i, NULL);
            }
        }
    } else {
        memory_clear(self->values, self->size * sizeof(void *));
    }

    self->cursor = 0;
}

void
array_destroy(array_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer == NULL) return;

    array_t *self = *self_pointer;
    array_purge(self);
    free(self->values);
    free(self);
    *self_pointer = NULL;
}

void
array_set_destroy_fn(array_t *self, destroy_fn_t *destroy_fn) {
    self->destroy_fn = destroy_fn;
}

array_t *
array_new_with(size_t size, destroy_fn_t *destroy_fn) {
    array_t *self = array_new(size);
    self->destroy_fn = destroy_fn;
    return self;
}

array_t *
array_new_auto(void) {
    return array_new(ARRAY_AUTO_SIZE);
}

array_t *
array_new_auto_with(destroy_fn_t *destroy_fn) {
    return array_new_with(ARRAY_AUTO_SIZE, destroy_fn);
}

size_t array_size(const array_t *self);
size_t array_grow_step(const array_t *self);
void array_set_grow_step(array_t *self, size_t grow_step);

size_t array_length(const array_t *self);
bool array_is_empty(const array_t *self);
bool array_is_full(const array_t *self);

void array_resize(array_t *self, size_t larger_size);

void *array_top(array_t *self);
void *array_pop(array_t *self);
void array_push(array_t *self, void *value);

void *array_get(const array_t *self, size_t index);
void *array_pick(const array_t *self, size_t back_index);

void array_set(array_t *self, size_t index, void *value);
