#include "index.h"

static uint8_t blending_table[16][4] = {
    { 0, 0, 1, 2 }, // bg bg sl fg tr
    { 0, 1, 2, 3 }, // bg sl fg ap
    { 0, 2, 3, 1 }, // bg fg ap sl
    { 0, 3, 1, 2 }, // bg ap sl fg
    { 1, 0, 1, 2 }, // sl bg sl fg
    { 0, 1, 2, 3 }, // bg sl fg ap tr
    { 1, 2, 3, 1 }, // sl fg ap sl
    { 1, 3, 1, 2 }, // sl ap sl fg
    { 2, 0, 1, 2 }, // fg bg sl fg
    { 2, 1, 2, 3 }, // fg sl fg ap
    { 0, 2, 3, 1 }, // bg fg ap sl tr
    { 2, 3, 1, 2 }, // fg ap sl fg
    { 3, 0, 1, 2 }, // ap bg sl fg
    { 3, 1, 2, 3 }, // ap sl fg ap
    { 3, 2, 3, 1 }, // ap fg ap sl
    { 0, 3, 1, 2 }, // bg ap sl fg tr
};

typedef enum {
    BG_BG_SL_FG_TR,
    BG_SL_FG_AP,
    BG_FG_AP_SL,
    BG_AP_SL_FG,
    SL_BG_SL_FG,
    BG_SL_FG_AP_TR,
    SL_FG_AP_SL,
    SL_AP_SL_FG,
    FG_BG_SL_FG,
    FG_SL_FG_AP,
    BG_FG_AP_SL_TR,
    FG_AP_SL_FG,
    AP_BG_SL_FG,
    AP_SL_FG_AP,
    AP_FG_AP_SL,
    BG_AP_SL_FG_TR,
} blending_t;

static bool
blending_is_transparent(uint8_t blending) {
    return
        (blending == 0x0) ||
        (blending == 0x5) ||
        (blending == 0xa) ||
        (blending == 0xf);
}

void
canvas_draw_icn_bytes(
    canvas_t *self,
    size_t x, size_t y,
    uint8_t *bytes,
    size_t width, size_t height,
    uint8_t blending
) {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            for (size_t line = 0; line < 8; line++) {
                size_t index = (row * 8 * width) + (col * 8 + line);
                uint8_t byte = bytes[index];
                for (uint8_t s = 0; s < 8; s++) {
                    uint8_t bit = ((byte << s) & 0x80) != 0;
                    color_t color = bit;
                    if (blending_is_transparent(blending) && color == 0) continue;

                    color_t blended = blending_table[blending][color];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        self->palette[blended]);
                }
            }
        }
    }
}

void
canvas_draw_chr_bytes(
    canvas_t *self,
    size_t x, size_t y,
    uint8_t *bytes,
    size_t width, size_t height,
    uint8_t blending
) {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            for (size_t line = 0; line < 8; line++) {
                size_t index = (row * 8 * 2 * width) + (col * 8 * 2 + line);
                uint8_t chr1 = bytes[index];
                uint8_t chr2 = bytes[index + 8];
                for (uint8_t s = 0; s < 8; s++) {
                    uint8_t bit1 = ((chr1 << s) & 0x80) != 0;
                    uint8_t bit2 = ((chr2 << s) & 0x80) != 0;
                    color_t color = bit1 + bit2 * 2;
                    if (blending_is_transparent(blending) && color == 0) continue;

                    color_t blended = blending_table[blending][color];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        self->palette[blended]);
                }
            }
        }
    }
}

void
canvas_draw_image(
    canvas_t *self,
    size_t x, size_t y,
    const char *path,
    uint8_t blending
) {
    uint8_t width = image_hex_width_from_path(path);
    uint8_t height = image_hex_height_from_path(path);
    uint8_t *bytes = canvas_asset_store_get(self, path);
    canvas_draw_chr_bytes(self, x, y, bytes, width, height, blending);
}

void
canvas_draw_image_button(
    canvas_t *self,
    size_t x, size_t y,
    const char *path,
    uint8_t blending,
    on_click_t *on_click
) {
    uint8_t width = image_hex_width_from_path(path);
    uint8_t height = image_hex_height_from_path(path);
    canvas_draw_image(self, x, y, path, blending);
    canvas_add_clickable_area(self, x, y, width * TILE, height * TILE, on_click);
}
