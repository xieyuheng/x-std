#include "index.h"

void
utf8_test(void) {
    printf("<utf8_test>\n");

    assert(utf8_byte_length('a') == 1);

    {
        const char *string = "中"; // 0xE4 0xB8 0xAD
        assert(utf8_byte_length(string[0]) == 3);
    }

    utf8_iter_t *iter = utf8_iter_new("abc 中文 123");

    //

    utf8_iter_destroy(&iter);

    printf("</utf8_test>\n");
}
