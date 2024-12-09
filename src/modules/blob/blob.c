#include "index.h"

// with a extra ending '\0' to be viewed as string.

struct blob_t {
    size_t length;
    uint8_t *bytes;
};
