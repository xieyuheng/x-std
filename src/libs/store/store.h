#pragma once

// file store with cache

store_t *store_new(const char *base);
void store_destroy(store_t **self_pointer);

const char *store_base(store_t *self);
void store_purge_cache(store_t *self);
