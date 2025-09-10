#include "index.h"

// The address of a block returned by malloc or realloc in GNU systems
// is always a multiple of eight (or sixteen on 64-bit systems).
// -- https://www.gnu.org/software/libc/manual/html_node/Aligned-Memory-Blocks.html

bool
pointer_is_8_bytes_aligned(void *pointer) {
    return (((uintptr_t) pointer) & ((uintptr_t) 0x7)) == 0;
}

void *
allocate(size_t size) {
    void *pointer = calloc(1, size);
    assert(pointer);
    assert(pointer_is_8_bytes_aligned(pointer));
    return pointer;
}

void *
allocate_pointers(size_t size) {
    return allocate(size * sizeof(void *));
}

void
destroy(void **value_pointer) {
    assert(value_pointer);
    if (*value_pointer) {
        void *value = *value_pointer;
        free(value);
        *value_pointer = NULL;
    }
}

void *
reallocate(void *pointer, size_t old_size, size_t new_size) {
    void *new_pointer = realloc(pointer, new_size);
    assert(new_pointer);
    assert(pointer_is_8_bytes_aligned(new_pointer));
    memory_clear((((char *) new_pointer) + old_size), new_size - old_size);
    return new_pointer;
}

void *
reallocate_pointers(void *pointer, size_t old_size, size_t new_size) {
    size_t unit_size = sizeof(void *);
    void *new_pointer = realloc(pointer, new_size * unit_size);
    assert(new_pointer);
    assert(pointer_is_8_bytes_aligned(new_pointer));
    memory_clear((((char *) new_pointer) + old_size * unit_size),
                 (new_size - old_size) * unit_size);
    return new_pointer;
}

bool
pointer_is_page_aligned(void *pointer) {
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    return (((uintptr_t) pointer) % page_size) == 0;
}

void *
allocate_page_aligned(size_t size) {
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    assert(page_size > 0);
    size_t real_size = ((size / page_size) + 1) * page_size;
    void *pointer = aligned_alloc(page_size, real_size);
    memory_clear(pointer, real_size);
    assert(pointer);
    assert(pointer_is_8_bytes_aligned(pointer));
    assert(pointer_is_page_aligned(pointer));
    return pointer;
}

void
memory_clear(void *pointer, size_t size) {
    memset(pointer, 0, size);
}
