#include "index.h"

void
text_test(void) {
    printf("<text_test>\n");

    {
        text_t *text = text_from_string("abc");

        text_destroy(&text);
    }

    {
        text_t *text = text_from_string("中文");

        text_destroy(&text);
    }



    printf("</text_test>\n");
}
