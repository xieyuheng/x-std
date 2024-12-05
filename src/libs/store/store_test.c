#include "index.h"

void
store_test(void) {
    printf("<store_test>\n");

    char *base = string_append(dirname(string_dup(__FILE__)), "/");
    store_t *store = store_new(base);

    //

    store_destroy(&store);

    printf("</store_test>\n");
}
