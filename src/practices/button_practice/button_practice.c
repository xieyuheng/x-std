#include "index.h"

struct button_practice_t {
    canvas_t *canvas;
    canvas_window_t *window;
    uint8_t *button_up_chr;
    uint8_t *button_down_chr;
};

button_practice_t *
button_practice_new(void) {
    button_practice_t *self = allocate(sizeof(button_practice_t));

    char *base = dirname(string_dup(__FILE__));
    const char *file_name = string_append(base, "/button10x10.chr");
    file_t *file = fopen(file_name, "rb");
    uint8_t *bytes = file_read_bytes(file);
    self->button_up_chr = chr_subimage(bytes, 0x10, 0, 0, 3, 3);
    self->button_down_chr = chr_subimage(bytes, 0x10, 3, 0, 3, 3);
    free(bytes);

    self->canvas = canvas_new(9 * TILE, 9 * TILE);
    self->window = canvas_window_new(self->canvas, 0x10);
    self->window->title = "button practice";

    return self;
}

void
button_practice_destroy(button_practice_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        button_practice_t *self = *self_pointer;
        canvas_window_destroy(&self->window);
        canvas_destroy(&self->canvas);
        free(self->button_up_chr);
        free(self->button_down_chr);
        free(self);
        *self_pointer = NULL;
    }
}

void
button_practice_start(void) {
    button_practice_t *self = button_practice_new();

    canvas_fill_bottom_right(self->canvas, 0, 0, 0);
    size_t x = 3 * TILE;
    size_t y = 3 * TILE;
    canvas_draw_chr(self->canvas, x, y, self->button_up_chr, 3, 3, 1);

    canvas_window_open(self->window);

    button_practice_destroy(&self);
}
