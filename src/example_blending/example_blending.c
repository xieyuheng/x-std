#include "index.h"

static void on_frame(void *state, canvas_t *canvas, uint64_t passed);

void
example_blending_start(void) {
    canvas_t *canvas = canvas_new(0x10 * TILE, 0x10 * TILE, 0x8);
    canvas->state = NULL;
    canvas->on_frame = (on_frame_t *) on_frame;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "example blending";

    canvas_open(canvas);
    canvas_destroy(&canvas);
}

void
on_frame(void *state, canvas_t *canvas, uint64_t passed) {
    (void) state;
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, BG_COLOR);
    canvas_clear_clickable_area(canvas);

    // render_button(state, canvas);
    // render_cursor(state, canvas);
}
