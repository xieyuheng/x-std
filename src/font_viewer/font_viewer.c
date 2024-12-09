#include "index.h"

#define WIDTH (60 * TILE)
#define HEIGHT (40 * TILE)
#define SCALE 4

static void
init_canvas_theme(canvas_t *canvas) {
    canvas->palette[BG_COLOR] = 0xffffffff;
    canvas->palette[SL_COLOR] = 0xff000000;
    canvas->palette[FG_COLOR] = 0xffffffff;
    canvas->palette[AP_COLOR] = 0xff000000;
}

static void
init_canvas_asset_store(canvas_t *canvas) {
    char *root = dirname(dirname(dirname(string_dup(__FILE__))));
    canvas_init_asset_store(canvas, string_append(root, "/assets"));
}

static void
init_canvas_font(canvas_t *canvas) {
    blob_t *blob = canvas_asset_store_get(canvas, "fonts/unifont_all-16.0.02.hex");
    canvas->font = font_from_hex_string(blob_string(blob));
}

font_viewer_t *
font_viewer_new(font_t *font) {
    font_viewer_t *self = new(font_viewer_t);

    self->blending = TR_AP_BLENDING;
    self->font = font;
    self->glyph = font_first_glyph(font);
    self->page = 0;

    canvas_t *canvas = canvas_new(WIDTH, HEIGHT, SCALE);
    canvas->state = self;
    canvas->title = "bifer";
    self->canvas = canvas;

    init_canvas_theme(canvas);
    init_canvas_asset_store(canvas);
    init_canvas_font(canvas);

    return self;
}

void
font_viewer_destroy(font_viewer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        font_viewer_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        font_destroy(&self->font);
        free(self);
        *self_pointer = NULL;
    }
}

static void
render_background_grid(font_viewer_t *self, canvas_t *canvas) {
    (void) self;

    for (size_t x = 0; x < WIDTH / TILE; x++) {
        for (size_t y = 0; y < HEIGHT / TILE; y++) {
            canvas_draw_pixel(canvas, x * TILE, y * TILE, 0xffff0000);
        }
    }
}

static void
render_glyph(font_viewer_t *self, canvas_t *canvas) {
    if (self->glyph) {
        size_t scale = TILE;
        canvas_draw_glyph(
            canvas,
            38 * TILE,
            4 * TILE,
            self->glyph,
            scale,
            self->blending);
    }
}

static void
render_glyph_info(font_viewer_t *self, canvas_t *canvas) {
    (void) self;
    (void) canvas;
}

static void
render_page(font_viewer_t *self, canvas_t *canvas) {
    size_t x_offset = 4 * TILE;
    size_t y_offset = 4 * TILE;
    size_t scale = 1;
    for (size_t row = 0; row < 16; row++) {
        for (size_t col = 0; col < 16; col++) {
            code_point_t code_point = self->page * (16 * 16) + row * 16 + col;
            glyph_t *glyph = font_get(self->font, code_point);
            canvas_draw_glyph(
                canvas,
                x_offset + col * 2 * TILE,
                y_offset + row * 2 * TILE,
                glyph,
                scale,
                self->blending);
        }
    }
}

static void
on_frame(font_viewer_t *self, canvas_t *canvas, uint64_t passed) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);

    (void) render_background_grid;
    // render_background_grid(self, canvas);

    render_glyph(self, canvas);
    render_glyph_info(self, canvas);
    render_page(self, canvas);
}

static void
on_key(
    font_viewer_t *self,
    canvas_t *canvas,
    const char *key_name,
    bool is_release
) {
    (void) canvas;

    if (is_release) {
        if (string_equal_mod_case(key_name, "tab")) {
            self->blending = (self->blending + 1) % 16;
        }

        if (string_equal_mod_case(key_name, "space")) {
            code_point_t code_point = glyph_code_point(self->glyph);
            glyph_t *next_glyph = font_next_glyph(self->font, code_point);
            if (next_glyph) {
                self->glyph = next_glyph;
            } else {
                self->glyph = font_first_glyph(self->font);
            }
        }
    }
}

void
font_viewer_start(font_t *font) {
    font_viewer_t *self = font_viewer_new(font);
    self->canvas->on_frame = (on_frame_t *) on_frame;
    self->canvas->on_key = (on_key_t *) on_key;

    canvas_open(self->canvas);

    font_viewer_destroy(&self);
}
