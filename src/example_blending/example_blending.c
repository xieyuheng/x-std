#include "index.h"

static void on_frame(void *state, canvas_t *canvas, uint64_t passed);

void
example_blending_start(void) {
    canvas_t *canvas = canvas_new(0x8 * TILE, 0x8 * TILE, 0x8);
    canvas->state = NULL;
    canvas->on_frame = (on_frame_t *) on_frame;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "example blending";

    canvas_open(canvas);
    canvas_destroy(&canvas);
}

static void render_blending_table(canvas_t *canvas);

void
on_frame(void *state, canvas_t *canvas, uint64_t passed) {
    (void) state;
    (void) passed;

    canvas->window->background_pixel = 0xffaaaaaa;
    canvas_fill_bottom_right(canvas, 0, 0, 0xffaaaaaa);
    canvas_clear_clickable_area(canvas);

    render_blending_table(canvas);
}

void
render_blending_table(canvas_t *canvas) {
    for (uint8_t x = 0; x < 4; x++) {
        for (uint8_t y = 0; y < 4; y++) {
            uint8_t blending = x + y * 4;
            canvas_draw_image(
                canvas,
                x * 2 * TILE,
                y * 2 * TILE,
                "blending-02x02.chr",
                blending);
        }
    }
}
