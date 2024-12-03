#include "index.h"

struct button_practice_t {
    canvas_window_t *window;
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

    canvas_t *canvas = canvas_new(9 * TILE, 9 * TILE);
    self->window = canvas_window_new(canvas, 0x10);
    self->window->title = "button practice";
    self->window->state = self;

    self->is_pressed = false;

    return self;
}

void
button_practice_destroy(button_practice_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        button_practice_t *self = *self_pointer;
        canvas_destroy(&self->window->canvas);
        canvas_window_destroy(&self->window);
        free(self->button_up_chr);
        free(self->button_down_chr);
        free(self);
        *self_pointer = NULL;
    }
}

static void
render_button(canvas_window_t *window, button_practice_t *self) {
    size_t x = 3 * TILE;
    size_t y = 3 * TILE;

    if (self->is_pressed) {
        canvas_draw_chr(window->canvas, x, y, self->button_down_chr, 3, 3, 1);

        // canvas_window_add_clickable_area(
        //     window,
        //     x, y,
        //     3 * TILE, 3 * TILE,
        //     button_on_click);

        // canvas_window_render_image_button(
        //     window,
        //     x, y,
        //     "asset-name",
        //     button_on_click);

    } else {
        canvas_draw_chr(window->canvas, x, y, self->button_up_chr, 3, 3, 1);
    }
}

static void
on_frame(canvas_window_t *window, button_practice_t *self, uint64_t expirations) {
    (void) expirations;

    self->window->background_pixel = self->window->canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(window->canvas, 0, 0, BG_COLOR);
    render_button(window, self);
}

static void
on_click(canvas_window_t *window, button_practice_t *self, size_t x, size_t y, uint8_t button, bool is_release) {
    (void) window;
    (void) self;

    (void) x;
    (void) y;

    if (button == 1) {
        if (is_release) {
            self->is_pressed = false;
        } else {
            self->is_pressed = true;
        }
    }
}

void
button_practice_start(void) {
    button_practice_t *self = button_practice_new();
    self->window->on_frame = (on_frame_t *) on_frame;
    self->window->on_click = (on_click_t *) on_click;

    canvas_window_open(self->window);

    button_practice_destroy(&self);
}
