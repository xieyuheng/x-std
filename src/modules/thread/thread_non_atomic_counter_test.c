#include "index.h"

static atomic_size_t global_count = 0;

// READ_ONCE(var) → atomic_load_explicit(&var, memory_order_relaxed)
// WRITE_ONCE(var, val) → atomic_store_explicit(&var, val, memory_order_relaxed)

static void
counter_add1(void) {
    size_t count = atomic_load_explicit(&global_count, memory_order_relaxed);
    atomic_store_explicit(&global_count, count, memory_order_relaxed);
}

static size_t
counter_read(void) {
    return atomic_load_explicit(&global_count, memory_order_relaxed);
}

// static void
// counter_add1(void) {
//     global_count++;
// }

// static size_t
// counter_read(void) {
//     return global_count;
// }

void
thread_non_atomic_counter_test(void) {
    printf("<thread_non_atomic_counter_test>\n");

    stack_t *thread_id_stack = stack_new();
    thread_fn_t *thread_fn = (thread_fn_t *) counter_add1;
    for (size_t i = 0; i < 100; i++) {
        thread_id_t thread_id = thread_start(thread_fn, NULL);
        stack_push(thread_id_stack, (void *) thread_id);
    }

    while (!stack_is_empty(thread_id_stack)) {
        thread_id_t thread_id = (thread_id_t) stack_pop(thread_id_stack);
        thread_wait(thread_id);
    }

    printf("count: %lu\n", counter_read());

    printf("</thread_non_atomic_counter_test>\n");
}
