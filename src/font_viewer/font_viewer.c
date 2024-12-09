#include "index.h"

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
    canvas->asset_base = string_append(root, "/assets");
    canvas_init_asset_store(canvas);
}

static void
init_canvas_font(canvas_t *canvas) {
    blob_t *blob = canvas_asset_store_get(canvas, "fonts/unifont_all-16.0.02.hex");
    canvas->font = font_from_hex_string(blob_string(blob));
}

font_viewer_t *
font_viewer_new(font_t *font) {
    font_viewer_t *self = new(font_viewer_t);

    self->width = 0x30 * TILE;
    self->height = 0x20 * TILE;
    self->blending = BG_AP_BLENDING;
    self->font = font;
    self->glyph = font_first_glyph(font);

    canvas_t *canvas = canvas_new(self->width, self->height, 0x4);
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
render_glyph(font_viewer_t *self, canvas_t *canvas) {
    if (self->glyph) {
        size_t scale = 8;
        canvas_draw_glyph(
            canvas,
            self->width / 4,
            self->height / 4,
            self->glyph,
            scale,
            self->blending);
    }
}

static void
render_glyph_info(font_viewer_t *self, canvas_t *canvas) {
    if (self->glyph) {
        size_t scale = 1;
        canvas_draw_text(
            canvas,
            self->width / 4,
            self->height / 4 * 3,
            text_from_string("abc 中文"),
            scale,
            self->blending);
    }
}

static void
on_frame(font_viewer_t *self, canvas_t *canvas, uint64_t passed) {
    (void) self;
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);

    render_glyph(self, canvas);
    render_glyph_info(self, canvas);
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
