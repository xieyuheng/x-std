#include "index.h"
#include "button_practice.h"

button_practice_t *
button_practice_new(void) {
    button_practice_t *self = allocate(sizeof(button_practice_t));
    // TODO
    return self;
}

void
button_practice_destroy(button_practice_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        button_practice_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
button_practice_start(void) {
    char *base = dirname(string_dup(__FILE__));
    const char *file_name = string_append(base, "/button10x10.chr");

    printf("[button_practice] file_name: %s\n", file_name);

    file_t *file = fopen(file_name, "rb");
    uint8_t *bytes = file_read_bytes(file);
    uint8_t *button_up_chr = chr_subimage(bytes, 0x10, 0, 0, 3, 3);
    uint8_t *button_down_chr = chr_subimage(bytes, 0x10, 3, 0, 3, 3);

    canvas_t *canvas = canvas_new(9 * TILE, 9 * TILE);
    canvas_window_t *window = canvas_window_new(canvas, 0x10);
    window->title = "button practice";

    canvas_fill_bottom_right(canvas, 0, 0, 0);
    size_t x = 3 * TILE;
    size_t y = 3 * TILE;
    canvas_draw_chr(canvas, x, y, button_up_chr, 3, 3, 1);
    (void) button_down_chr;

    canvas_window_open(window);

    canvas_window_destroy(&window);
    canvas_destroy(&canvas);
}
