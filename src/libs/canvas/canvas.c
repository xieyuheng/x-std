#include "index.h"

canvas_t *
canvas_new(size_t width, size_t height, size_t scale) {
    canvas_t *self = allocate(sizeof(canvas_t));
    self->width = width;
    self->height = height;
    self->scale = scale;

    self->pixels = allocate(self->width * self->height * sizeof(uint32_t));

    self->palette[BG_COLOR] = 0xff0047A0;
    self->palette[SL_COLOR] = 0xffcd2e3a;
    self->palette[FG_COLOR] = 0xff000000;
    self->palette[AP_COLOR] = 0xffffffff;

    self->window = canvas_window_new(self);
    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self->pixels);
        canvas_window_destroy(&self->window);
        free(self);
        *self_pointer = NULL;
    }
}

void
canvas_open(canvas_t *self) {
    canvas_window_open(self->window);
}

void
canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    self->pixels[y * self->width + x] = pixel;
}

void
canvas_draw_pixel(canvas_t *self, size_t x, size_t y, color_t color) {
    canvas_put_pixel(self, x, y, self->palette[color]);
}

void
canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, y + j, color);
        }
    }
}

void
canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, y + j, color);
        }
    }
}

void
canvas_fill_top_right(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, j, color);
        }
    }
}

void
canvas_fill_top_left(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, j, color);
        }
    }
}

static uint8_t blending_table[4][16] = {
    {0, 0, 0, 0, 1, 0, 1, 1, 2, 2, 0, 2, 3, 3, 3, 0},
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3},
    {1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1},
    {2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2},
};

void
canvas_draw_icn(
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
                    color_t blended = blending_table[color][blending];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        blended);
                }
            }
        }
    }
}

void
canvas_draw_chr(
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
                    color_t blended = blending_table[color][blending];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        blended);
                }
            }
        }
    }
}
