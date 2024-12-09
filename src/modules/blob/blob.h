#pragma once

blob_t *blob_new(size_t length);
void blob_destroy(blob_t **self_pointer);

size_t blob_length(blob_t *self);
uint8_t *blob_bytes(blob_t *self);
char *blob_string(blob_t *self);
