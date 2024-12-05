#pragma once

// file store with cache

store_t *store_new(const char *base);
void store_destroy(store_t **self_pointer);
