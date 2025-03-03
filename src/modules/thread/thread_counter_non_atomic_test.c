#include "index.h"

static atomic_size_t global_count = 0;

static void *
counter_add1(void *arg) {
    (void) arg;
    size_t count = volatile_load(&global_count);
    sleep(0); // let other threads run
    volatile_store(&global_count, count + 1);
    return NULL;
}

static size_t
counter_read(void) {
    return volatile_load(&global_count);
}

void
thread_counter_non_atomic_test(void) {
    printf("<thread_counter_non_atomic_test>\n");
    clock_t start_clock = clock();

    stack_t *stack = stack_new();

    thread_fn_t *thread_fn = (thread_fn_t *) counter_add1;
    for (size_t i = 0; i < 1000; i++) {
        thread_id_t thread_id = thread_start(thread_fn, NULL);
        stack_push(stack, (void *) thread_id);
    }

    while (!stack_is_empty(stack)) {
        thread_id_t thread_id = (thread_id_t) stack_pop(stack);
        thread_wait(thread_id);
    }

    stack_destroy(&stack);

    printf("final count: %lu\n", counter_read());
    printf("elapsed seconds: %fs\n", clock_elapsed_seconds(start_clock));
    printf("</thread_counter_non_atomic_test>\n");
}
