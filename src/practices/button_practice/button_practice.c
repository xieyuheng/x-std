#include "index.h"

struct button_practice_t {
    canvas_t *canvas;
    uint8_t *button_up_chr;
    uint8_t *button_down_chr;
    bool is_pressed;
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

    self->canvas = canvas_new(9 * TILE, 9 * TILE, 0x10);
    self->canvas->title = "button practice";
    self->canvas->state = self;

    self->is_pressed = false;

    return self;
}

void
button_practice_destroy(button_practice_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        button_practice_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        free(self->button_up_chr);
        free(self->button_down_chr);
        free(self);
        *self_pointer = NULL;
    }
}

static void
button_on_click(
    button_practice_t *self,
    canvas_t *canvas,
    size_t x,
    size_t y,
    uint8_t button,
    bool is_release
) {
    (void) canvas;
    (void) self;

    (void) x;
    (void) y;

    if (button == 1) {
        if (is_release) {
            self->is_pressed = false;
            printf("!");
        } else {
            self->is_pressed = true;
        }
    }
}

static void
render_button(button_practice_t *self, canvas_t *canvas) {
    size_t x = 3 * TILE;
    size_t y = 3 * TILE;
    size_t width = 3 * TILE;
    size_t height = 3 * TILE;

    if (self->is_pressed) {
        canvas_draw_chr_image(canvas, x, y, self->button_down_chr, 3, 3, 1);
        canvas_add_clickable_area(
            canvas, x, y, width, height,
            (on_click_t *) button_on_click);
    } else {
        canvas_draw_chr_image(canvas, x, y, self->button_up_chr, 3, 3, 1);
        canvas_add_clickable_area(
            canvas, x, y, width, height,
            (on_click_t *) button_on_click);
    }
}

static void
on_frame(
    button_practice_t *self,
    canvas_t *canvas,
    uint64_t passed
) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, BG_COLOR);
    canvas_clear_clickable_area(canvas);
    render_button(self, canvas);
}

void
button_practice_start(void) {
    button_practice_t *self = button_practice_new();
    self->canvas->on_frame = (on_frame_t *) on_frame;
    canvas_open(self->canvas);
    button_practice_destroy(&self);
}
