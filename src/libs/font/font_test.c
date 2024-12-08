#include "index.h"

void
font_test(void) {
    glyph_test();

    printf("<font_test>\n");

    {
        font_t *font = font_new();
        font_destroy(&font);
    }

    char *base = dirname(string_dup(__FILE__));
    char *file_name = string_append(base, "/unifont-ascii.hex");
    file_t *file = file_open_or_fail(file_name, "r");
    font_t *font = font_from_hex_file(file);

    glyph_iter_t *glyph_iter = glyph_iter_new(font);
    glyph_t *glyph = glyph_iter_start(glyph_iter);
    while (glyph) {
        printf("ascii code point: ox%x\n", glyph_code_point(glyph));
        printf("\n");
        glyph_print_ascii_art(glyph, ' ', '#');
        printf("\n");

        glyph = glyph_iter_next(glyph_iter);
    }

    font_destroy(&font);

    printf("</font_test>\n");
}
