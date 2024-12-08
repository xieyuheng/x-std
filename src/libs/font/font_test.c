#include "index.h"

void
font_test(void) {
    printf("<font_test>\n");

    glyph_t *glyph = glyph_parse_hex("0041:0000000018242442427E424242420000");

    for (size_t y = 0; y < glyph_height(glyph); y++) {
        for (size_t x = 0; x < glyph_width(glyph); x++) {
            bool dot = glyph_get(glyph, x, y);
            if (dot) printf("AA");
            else printf("--");
        }

        printf("\n");
    }

    glyph_set(glyph, 0x0, 0x0, true);
    glyph_set(glyph, 0x7, 0x0, true);
    glyph_set(glyph, 0x0, 0xf, true);
    glyph_set(glyph, 0x7, 0xf, true);

    for (size_t y = 0; y < glyph_height(glyph); y++) {
        for (size_t x = 0; x < glyph_width(glyph); x++) {
            bool dot = glyph_get(glyph, x, y);
            if (dot) printf("AA");
            else printf("--");
        }

        printf("\n");
    }

    glyph_set(glyph, 0x0, 0x0, false);
    glyph_set(glyph, 0x7, 0x0, false);
    glyph_set(glyph, 0x0, 0xf, false);
    glyph_set(glyph, 0x7, 0xf, false);

    for (size_t y = 0; y < glyph_height(glyph); y++) {
        for (size_t x = 0; x < glyph_width(glyph); x++) {
            bool dot = glyph_get(glyph, x, y);
            if (dot) printf("AA");
            else printf("--");
        }

        printf("\n");
    }

    glyph_destroy(&glyph);

    printf("</font_test>\n");
}
