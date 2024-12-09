#include "index.h"

void
blob_test(void) {
    printf("<blob_test>\n");

    blob_t *blob = blob_new(3);
    blob_bytes(blob)[0] = 'a';
    blob_bytes(blob)[1] = 'b';
    blob_bytes(blob)[2] = 'c';

    assert(string_equal(blob_string(blob), "abc"));

    printf("</blob_test>\n");
}
