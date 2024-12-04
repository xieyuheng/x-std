#include "index.h"

struct entry_t {
    char *key;
    void *item;
};

typedef struct entry_t entry_t;

// static
entry_t *
entry_new(char *key, void *item) {
    entry_t *self = allocate(sizeof(entry_t));
    self->key = key;
    self->item = item;
    return self;
}

struct dict_t {
    list_t *entry_list;
};
