#include "index.h"

static atomic_size_t global_count = 0;

static void
counter_add1(void) {
    atomic_fetch_add(&global_count, 1);
}

static size_t
counter_read(void) {
    return atomic_load(&global_count);
}

void
thread_counter_atomic_test(void) {
    printf("<thread_counter_atomic_test>\n");

    stack_t *thread_id_stack = stack_new();
    thread_fn_t *thread_fn = (thread_fn_t *) counter_add1;
    for (size_t i = 0; i < 10000; i++) {
        thread_id_t thread_id = thread_start(thread_fn, NULL);
        stack_push(thread_id_stack, (void *) thread_id);
    }

    while (!stack_is_empty(thread_id_stack)) {
        thread_id_t thread_id = (thread_id_t) stack_pop(thread_id_stack);
        thread_wait(thread_id);
    }

    printf("count: %lu\n", counter_read());

    printf("</thread_counter_atomic_test>\n");
}
