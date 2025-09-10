#pragma once

bool pointer_is_8_bytes_aligned(void *pointer);

// clear memory to zero
void *allocate(size_t size);
void *allocate_pointers(size_t size);
void destroy(void **value_pointer);

// clear new memory to zero
void *reallocate(void *pointer, size_t old_size, size_t new_size);
void *reallocate_pointers(void *pointer, size_t old_size, size_t new_size);

bool pointer_is_page_aligned(void *pointer);

// aligned to page to avoid false sharing
void *allocate_page_aligned(size_t size);

void memory_clear(void *pointer, size_t size);
