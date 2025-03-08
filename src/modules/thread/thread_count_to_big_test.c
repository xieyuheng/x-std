#include "index.h"

#define BIG 100000

static _Atomic uint64_t count = 0;

static void *
count_to_big(void *arg) {
    (void) arg;

    for (size_t i = 0; i < BIG; i++) {
        volatile_store(&count, volatile_load(&count) + 1);
        // count++;
    }

    return NULL;
}

void
thread_count_to_big_test(void) {
    printf("<thread_count_to_big_test>\n");

    thread_id_t thread_id_1 = thread_start((thread_fn_t *) count_to_big, NULL);
    thread_id_t thread_id_2 = thread_start((thread_fn_t *) count_to_big, NULL);

    thread_wait(thread_id_1);
    thread_wait(thread_id_2);

    printf("count: %lu\n", count);

    printf("</thread_count_to_big_test>\n");
}
