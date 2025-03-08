#include "index.h"

void
thread_test(void) {
    printf("<thread_test>\n");

    thread_start_test();
    thread_counter_non_atomic_test();
    thread_counter_atomic_test();
    thread_counter_stat_test();
    thread_counter_stat_eventual_test();
    thread_count_to_big_test();
    thread_weak_memory_dekker_test();

    printf("</thread_test>\n");
}
