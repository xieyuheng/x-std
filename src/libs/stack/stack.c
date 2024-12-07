#include "index.h"

#define STACK_BLOCK_SIZE 1024

struct stack_t {
    size_t block_size;
    list_t *array_list;
    destructor_t *destructor;
};

stack_t *
stack_new(void) {
    stack_t *self = new(stack_t);
    self->block_size = STACK_BLOCK_SIZE;
    self->array_list = list_new();
    return self;
}

// void
// stack_purge(stack_t *self) {
//     assert(self);
//     while(!stack_is_empty(self)) {
//         void* item = stack_pop(self);
//         if (self->destructor)
//             self->destructor(&item);
//     }
// }

// void
// stack_destroy(stack_t **self_pointer) {
//     assert(self_pointer);
//     if (*self_pointer) {
//         stack_t *self = *self_pointer;
//         stack_purge(self);
//         free(self);
//         *self_pointer = NULL;
//     }
// }

void
stack_set_destructor(
    stack_t *self,
    destructor_t *destructor
) {
    self->destructor = destructor;
}

stack_t *
stack_new_with(destructor_t *destructor) {
    stack_t *self = stack_new();
    self->destructor = destructor;
    return self;
}

size_t
stack_length(const stack_t *self) {
    size_t length = 0;
    array_t *array = list_start(self->array_list);
    while (array) {
        length += array_length(array);
        array = list_next(self->array_list);
    }

    return length;
}

bool
stack_is_empty(const stack_t *self) {
    return list_is_empty(self->array_list);
}

void *
stack_top(stack_t *self) {
    array_t *array = list_start(self->array_list);
    assert(array);
    return array_top(array);
}

// void *
// stack_pop(stack_t *self) {
//     array_t *array = list_start(self->array_list);
//     assert(array);
//     // TODO
//     void* item = self->items[self->cursor];
//     return item;
// }

// void
// stack_push(stack_t *self, void *item) {
//     self->items[self->cursor] = item;
//     self->cursor++;
// }

// void *
// stack_get(stack_t *self, size_t index) {
//     assert(index < self->cursor);
//     return self->items[index];
// }

// void *
// stack_pick(stack_t *self, size_t index) {
//     assert(index < self->cursor);
//     return self->items[self->cursor - 1 - index];
// }
