#include "index.h"

uint8_t
utf8_byte_length(char c) {
    uint8_t byte =  c;
    uint8_t pattern_1 = 0x00; // 0b0_______ >> 7
    uint8_t pattern_2 = 0x06; // 0b110_____ >> 5
    uint8_t pattern_3 = 0x0E; // 0b1110____ >> 4
    uint8_t pattern_4 = 0x1E; // 0b11110___ >> 3

    if (byte >> 7 == pattern_1) return 1;
    if (byte >> 5 == pattern_2) return 2;
    if (byte >> 4 == pattern_3) return 3;
    if (byte >> 3 == pattern_4) return 4;

    fprintf(stderr, "[utf8_byte_length] invalid utf8: 0x%x\n", byte);

    exit(1);
}

