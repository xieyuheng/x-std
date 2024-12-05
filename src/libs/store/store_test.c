#include "index.h"

void
store_test(void) {
    printf("<store_test>\n");

    char *base = string_append(dirname(string_dup(__FILE__)), "/");
    store_t *store = store_new(base);

    assert(store_has(store, "abc.txt"));
    assert(store_has(store, "123.txt"));
    // assert(!store_has(store, "xyz.txt"));
    // assert(!store_has(store, "456.txt"));

    {
        uint8_t *bytes = store_get(store, "abc.txt");
        assert(bytes[0] == 'a');
        assert(bytes[1] == 'b');
        assert(bytes[2] == 'c');
    }

    {
        uint8_t *bytes = store_get(store, "123.txt");
        assert(bytes[0] == '1');
        assert(bytes[1] == '2');
        assert(bytes[2] == '3');
    }

    //

    store_destroy(&store);

    printf("</store_test>\n");
}
