#pragma once

struct practice_button_t {
    void *todo;
};

typedef struct practice_button_t practice_button_t;

practice_button_t *practice_button_new(void);

void button_practice(void);
