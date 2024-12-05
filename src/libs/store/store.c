#include "index.h"

struct store_t {
    const char *base;
    dict_t *cache_dict;
};

store_t *
store_new(const char *base) {
    store_t *self = allocate(sizeof(store_t));
    self->base = base;
    self->cache_dict = dict_new();
    return self;
}
