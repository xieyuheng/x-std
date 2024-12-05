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

void
store_purge_cache(store_t *self) {
    dict_purge(self->cache_dict);
}

uint8_t *
store_get_from_cache(store_t *self, const char* path) {
    return dict_get(self->cache_dict, path);
}

uint8_t *
store_get(store_t *self, const char* path) {
    uint8_t *cached_bytes = store_get_from_cache(self, path);
    if (cached_bytes) {
        return cached_bytes;
    }

    return NULL;
}

bool
store_has(store_t *self, const char* path) {
    uint8_t *bytes = store_get(self, path);
    if (bytes) {
        return true;
    } else {
        return false;
    }
}
