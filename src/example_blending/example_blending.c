#include "index.h"

void
example_blending_start(void) {
    canvas_t *canvas = canvas_new(0x10 * TILE, 0x10 * TILE, 0x8);
    canvas->state = NULL;
    // canvas->on_frame = (on_frame_t *) on_frame;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "example blending";

    canvas_open(canvas);
    canvas_destroy(&canvas);
}
