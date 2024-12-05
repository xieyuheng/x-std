#pragma once

// asset file with cache

struct asset_store_t {
    const char *base;
    dict_t *cache_dict;
};
