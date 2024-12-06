#include "index.h"

typedef struct {
    bool is_pressed;
} state_t;

static void on_frame(state_t *state, canvas_t *canvas, uint64_t passed);

void
example_button_start(void) {
    state_t state;
    state.is_pressed = false;

    canvas_t *canvas = canvas_new(9 * TILE, 9 * TILE, 0x10);
    canvas->state = &state;
    canvas->on_frame = (on_frame_t *) on_frame;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->hide_system_cursor = true;
    canvas->title = "example button";

    canvas_open(canvas);
    canvas_destroy(&canvas);
}

static void render_button(state_t *state, canvas_t *canvas);
static void render_cursor(state_t *state, canvas_t *canvas);

void
on_frame(state_t *state, canvas_t *canvas, uint64_t passed) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, BG_COLOR);
    canvas_clear_clickable_area(canvas);

    render_button(state, canvas);
    render_cursor(state, canvas);
}

void
render_cursor(state_t *state, canvas_t *canvas) {
    (void) state;

    size_t x = canvas->cursor->x;
    size_t y = canvas->cursor->y;

    if (state->is_pressed) {
        canvas_draw_image(canvas, x, y, "cursor-01x01.chr", 0xf);
    } else {
        canvas_draw_image(canvas, x, y, "cursor-01x01.chr", 0x5);
    }
}

static void on_click_button(state_t *state, canvas_t *canvas, uint8_t button, bool is_release);

void
render_button(state_t *state, canvas_t *canvas) {
    size_t x = 3 * TILE;
    size_t y = 3 * TILE;

    if (state->is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "button-down-03x03.chr", 0x1,
            (on_click_t *) on_click_button);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "button-up-03x03.chr", 0x1,
            (on_click_t *) on_click_button);
    }
}

void
on_click_button(state_t *state, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) state;
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            state->is_pressed = false;
            printf("!");
        } else {
            state->is_pressed = true;
        }
    }
}
