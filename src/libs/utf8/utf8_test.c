#include "index.h"

void
utf8_test(void) {
    printf("<utf8_test>\n");

    assert(utf8_byte_length('a') == 1);

    {
        const char *string = "中"; // 0xE4 0xB8 0xAD
        assert(utf8_byte_length(string[0]) == 3);
    }

    {
        const char *string = "中";
        assert(utf8_code_point(string) == 0x00004E2D);
    }

    {
        const char *string = "文";
        assert(utf8_code_point(string) == 0x00006587);
    }

    {
        const char *string = "abc";
        assert(utf8_code_point(string) == 0x61);
        assert(utf8_code_point(string+1) == 0x62);
        assert(utf8_code_point(string+2) == 0x63);
    }

    {
        const char *string = "abc 中文 123";
        utf8_iter_t *iter = utf8_iter_new(string);

        code_point_t code_point = utf8_iter_start(iter);
        printf("testing string: %s\n", string);
        while (code_point) {
            printf("code_point: 0x%x\n", code_point);
            code_point = utf8_iter_next(iter);
        }

        utf8_iter_destroy(&iter);
    }

    {
        const char *string = "";
        utf8_iter_t *iter = utf8_iter_new(string);
        code_point_t code_point = utf8_iter_start(iter);
        assert(code_point == 0);
        utf8_iter_destroy(&iter);
    }

    printf("</utf8_test>\n");
}
