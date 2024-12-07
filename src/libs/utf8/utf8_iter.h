#pragma once

struct utf8_iter_t {
    size_t cursor;
    const char *string;
};

utf8_iter_t *utf8_iter_new(const char *string);
