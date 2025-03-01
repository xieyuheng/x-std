#include "index.h"

static void *
example_thread_fn(char *message) {
    printf("[example_thread_fn] %s\n", message);
    return (void *) strlen(message);
}

static void
thread_start_test(void) {
    printf("<thread_start_test>\n");

    char *message = string_copy("hello thread");
    thread_fn_t *thread_fn = (thread_fn_t *) example_thread_fn;
    thread_id_t thread_id = thread_start(thread_fn, message);

    printf("thread created: %lu\n", thread_id);
    size_t length = (size_t) thread_wait(thread_id);
    printf("thread returned: %lu\n", length);

    printf("</thread_start_test>\n");
}

void
thread_test(void) {
    printf("<thread_test>\n");

    thread_start_test();
    thread_counter_non_atomic_test();
    thread_counter_atomic_test();

    printf("</thread_test>\n");
}
