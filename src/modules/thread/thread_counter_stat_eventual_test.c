#include "index.h"

static void *
counter_add1(atomic_size_t *count_pointer) {
    size_t count = volatile_load(count_pointer);
    sleep(0); // let other threads run
    volatile_store(count_pointer, count + 1);
    return NULL;
}

#define THREAD_NUMBER 1000

static atomic_size_t counts[THREAD_NUMBER];

static atomic_size_t global_count = 0;
static atomic_bool eventual_run_p = false;

static void *
eventual(void *arg) {
    (void) arg;

    while (volatile_load(&eventual_run_p)) {
        size_t total_count = 0;
        for (size_t i = 0; i < THREAD_NUMBER; i++) {
            total_count += volatile_load(&counts[i]);
        }

        volatile_store(&global_count, total_count);
    }

    return NULL;
}

static size_t
counter_read(void) {
    return volatile_load(&global_count);
}

void
thread_counter_stat_eventual_test(void) {
    printf("<thread_counter_stat_eventual_test>\n");
    clock_t start_clock = clock();

    list_t *list = list_new();

    thread_id_t eventual_thread_id = thread_start(eventual, NULL);

    volatile_store(&eventual_run_p, true);

    thread_fn_t *thread_fn = (thread_fn_t *) counter_add1;
    for (size_t i = 0; i < THREAD_NUMBER; i++) {
        thread_id_t thread_id = thread_start(thread_fn, &counts[i]);
        list_push(list, (void *) thread_id);
    }

    while (!list_is_empty(list)) {
        thread_id_t thread_id = (thread_id_t) list_pop(list);
        thread_wait(thread_id);
    }

    volatile_store(&eventual_run_p, false);
    thread_wait(eventual_thread_id);

    list_destroy(&list);

    printf("final count: %lu\n", counter_read());
    printf("elapsed seconds: %fs\n", clock_elapsed_seconds(start_clock));
    printf("</thread_counter_stat_eventual_test>\n");
}
