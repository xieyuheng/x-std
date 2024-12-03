#pragma once

// About the four colors:
// - https://wiki.xxiivv.com/site/theme.html

typedef enum {
    BG_COLOR = 0, // Background/alpha
    SL_COLOR = 1, // Selection
    FG_COLOR = 2, // Foreground
    AP_COLOR = 3, // Application
} palette_color_t;


typedef void (on_key_t)(canvas_t *self, void *state, const char *key_name, bool is_release);
typedef void (on_click_t)(canvas_t *self, void *state, size_t x, size_t y, uint8_t button, bool is_release);
typedef void (on_frame_t)(canvas_t *self, void *state, uint64_t expirations);

// The width and height of canvas are measured in tile.
struct canvas_t {
    size_t width, height;

    // scale defines the ratio between
    // canvas pixel and screen pixel.
    size_t scale;

    uint32_t *pixels;
    uint32_t palette[4];

    canvas_window_t *window;
    const char *title;

    void *state;
    on_key_t *on_key;
    on_click_t *on_click;
    on_frame_t *on_frame;
};

canvas_t *canvas_new(size_t width, size_t height, size_t scale);
void canvas_destroy(canvas_t **self_pointer);

void canvas_open(canvas_t *self);

// The x and y position are measured in pixel.

void canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_draw_pixel(canvas_t *self, size_t x, size_t y, palette_color_t color);

void canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_top_right(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_top_left(canvas_t *self, size_t x, size_t y, palette_color_t color);

// The width and height of image are measured in tile.

void canvas_draw_icn(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
void canvas_draw_chr(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
