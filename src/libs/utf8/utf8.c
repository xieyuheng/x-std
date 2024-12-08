#include "index.h"

uint8_t
utf8_char_length(char c) {
    uint8_t byte =  c;
    uint8_t pattern_1 = 0x00; // 0b0_______ >> 7
    uint8_t pattern_2 = 0x06; // 0b110_____ >> 5
    uint8_t pattern_3 = 0x0E; // 0b1110____ >> 4
    uint8_t pattern_4 = 0x1E; // 0b11110___ >> 3

    if (byte >> 7 == pattern_1) return 1;
    if (byte >> 5 == pattern_2) return 2;
    if (byte >> 4 == pattern_3) return 3;
    if (byte >> 3 == pattern_4) return 4;

    fprintf(stderr, "[utf8_char_length] invalid utf8: 0x%x\n", byte);
    exit(1);
}

code_point_t
utf8_code_point(const char *string) {
    uint8_t mask_2 = 0x1F; // 0b00011111
    uint8_t mask_3 = 0x0F; // 0b00001111
    uint8_t mask_4 = 0x07; // 0b00000111
    uint8_t mask_r = 0x3F; // 0b00111111

    uint8_t byte_length = utf8_char_length(string[0]);
    switch (byte_length) {
    case 1: {
        return (uint8_t) string[0];
    }

    case 2: {
        uint8_t byte_1 = string[0];
        uint8_t byte_2 = string[1];
        return
            (((code_point_t) (mask_2 & byte_1)) << 6) +
            (((code_point_t) (mask_r & byte_2)) << 0);
    }

    case 3: {
        uint8_t byte_1 = string[0];
        uint8_t byte_2 = string[1];
        uint8_t byte_3 = string[2];
        return
            (((code_point_t) (mask_3 & byte_1)) << 12) +
            (((code_point_t) (mask_r & byte_2)) << 6) +
            (((code_point_t) (mask_r & byte_3)) << 0);
    }

    case 4: {
        uint8_t byte_1 = string[0];
        uint8_t byte_2 = string[1];
        uint8_t byte_3 = string[2];
        uint8_t byte_4 = string[3];
        return
            (((code_point_t) (mask_4 & byte_1)) << 18) +
            (((code_point_t) (mask_r & byte_2)) << 12) +
            (((code_point_t) (mask_r & byte_3)) << 6) +
            (((code_point_t) (mask_r & byte_4)) << 0);
    }
    }

    fprintf(stderr, "[utf8_code_point] invalid byte length: %u\n", byte_length);
    exit(1);
}

size_t
utf8_string_length(const char *string) {
    size_t length = 0;
    utf8_iter_t *iter = utf8_iter_new(string);
    code_point_t code_point = utf8_iter_start(iter);
    while (code_point) {
        length++;
        code_point = utf8_iter_next(iter);
    }

    utf8_iter_destroy(&iter);
    return length;
}
