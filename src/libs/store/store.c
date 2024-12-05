#include "index.h"

struct store_t {
    const char *base;
    dict_t *cache_dict;
};
