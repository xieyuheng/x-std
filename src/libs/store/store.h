#pragma once

// asset file with cache

struct store_t {
    const char *base;
    dict_t *cache_dict;
};
