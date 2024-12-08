#include "index.h"

void
text_test(void) {
    printf("<text_test>\n");

    {
        text_t *text = text_from_string("abc");
        assert(text_length(text) == 3);
        assert(text_get(text, 0) == 0x61);
        assert(text_get(text, 1) == 0x62);
        assert(text_get(text, 2) == 0x63);
        text_destroy(&text);
    }

    {
        text_t *text = text_from_string("中文");
        assert(text_length(text) == 2);
        assert(text_get(text, 0) == 0x4e2d);
        assert(text_get(text, 1) == 0x6587);
        text_destroy(&text);
    }

    printf("</text_test>\n");
}
