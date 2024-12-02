#pragma once

struct button_practice_t {
    void *todo;
};

button_practice_t *button_practice_new(void);
void button_practice_destroy(button_practice_t **self_pointer);

void button_practice(void);
