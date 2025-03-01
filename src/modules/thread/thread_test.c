#include "index.h"

void
thread_test(void) {
    printf("<thread_test>\n");

    thread_start_test();
    thread_counter_non_atomic_test();
    thread_counter_atomic_test();

    printf("</thread_test>\n");
}
