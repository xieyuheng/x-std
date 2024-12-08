#include "index.h"

void
utf8_test(void) {
    printf("<utf8_test>\n");

    assert(utf8_char_length('a') == 1);

    {
        const char *string = "中"; // 0xE4 0xB8 0xAD
        assert(utf8_char_length(string[0]) == 3);
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
        size_t index = 0;
        while (code_point) {
            if (index == 0) assert(code_point == 0x61);
            if (index == 1) assert(code_point == 0x62);
            if (index == 2) assert(code_point == 0x63);
            if (index == 3) assert(code_point == 0x20);
            if (index == 4) assert(code_point == 0x4e2d);
            if (index == 5) assert(code_point == 0x6587);
            if (index == 6) assert(code_point == 0x20);
            if (index == 7) assert(code_point == 0x31);
            if (index == 8) assert(code_point == 0x32);
            if (index == 9) assert(code_point == 0x33);

            code_point = utf8_iter_next(iter);
            index++;
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
