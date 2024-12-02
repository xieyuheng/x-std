#pragma once

struct button_practice_t {
    void *todo;
};

typedef struct button_practice_t button_practice_t;

button_practice_t *button_practice_new(void);

void button_practice(void);
