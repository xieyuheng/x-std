#include "index.h"

static int x, y;
static int a, b;

static void *
thread_fn_1(void *arg) {
    (void) arg;

    return NULL;
}

static void *
thread_fn_2(void *arg) {
    (void) arg;

    return NULL;
}

void
thread_weak_memory_dekker_test(void) {
    printf("<thread_weak_memory_dekker_test>\n");

    size_t count = 0;

    do {
        x = 0;
        y = 0;

        thread_id_t thread_id_1 = thread_start(thread_fn_1, NULL);
        thread_id_t thread_id_2 = thread_start(thread_fn_2, NULL);

        thread_wait(thread_id_1);
        thread_wait(thread_id_2);

        count++;
    } while (a != 0 || b != 0);

    printf("count: %lu\n", count);

    printf("</thread_weak_memory_dekker_test>\n");
}
