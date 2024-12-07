#include "index.h"

editor_t *
editor_new(void) {
    editor_t *self = new(editor_t);
    canvas_t *canvas = canvas_new(0xa * TILE, 0xa * TILE, 0x8);
    canvas->state = self;
    // canvas->on_frame = (on_frame_t *) on_frame;
    canvas->asset_base = dirname(string_dup(__FILE__));
    canvas->title = "bifer";
    self->canvas = canvas;
    return self;
}
