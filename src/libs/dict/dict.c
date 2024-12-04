#include "index.h"

struct entry_t {
    char *key;
    void *item;
};

typedef struct entry_t entry_t;

entry_t *entry_new(char *key, void *item);
void entry_destroy(entry_t **self_pointer);

entry_t *
entry_new(char *key, void *item) {
    entry_t *self = allocate(sizeof(entry_t));
    self->key = key;
    self->item = item;
    return self;
}

void
entry_destroy(entry_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        entry_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

struct dict_t {
    list_t *entry_list;
};
