#include "index.h"

struct store_t {
    const char *base;
    dict_t *cache_dict;
};

store_t *
store_new(const char *base) {
    store_t *self = new(store_t);
    self->base = base;
    self->cache_dict = dict_new_with((destructor_t *) destroy);
    return self;
}

void
store_destroy(store_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        store_t *self = *self_pointer;
        dict_destroy(&self->cache_dict);
        free(self);
        *self_pointer = NULL;
    }
}

const char *
store_base(store_t *self) {
    return self->base;
}
