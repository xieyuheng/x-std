#include "index.h"

void
utf8_test(void) {
    printf("<utf8_test>\n");

    utf8_iter_t *iter = utf8_iter_new("abc 中文 123");

    //

    utf8_iter_destroy(&iter);

    printf("</utf8_test>\n");
}
