#include "index.h"

void
code_test(void) {
    printf("<code_test>\n");

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".";

        assert(code_max_lineno(text) == 3);
    }

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".\n";

        assert(code_max_lineno(text) == 4);
    }

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".\n";

        assert(code_lineno_of_index(text, 0) == 1);
        assert(code_lineno_of_index(text, 1) == 1);
        assert(code_lineno_of_index(text, 100) == 4);
    }

    printf("</code_test>\n");
}
