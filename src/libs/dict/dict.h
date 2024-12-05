#pragma once

// a dist is a string to pointer kv-map.

dict_t *dict_new(void);
void dict_destroy(dict_t **self_pointer);
void dict_set_destructor(dict_t *self, destructor_t *destructor);
