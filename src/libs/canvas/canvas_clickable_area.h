#pragma once

struct canvas_clickable_area_t {
    size_t x, y;
    size_t width, height;
    on_click_t *on_click;
};

canvas_clickable_area_t *canvas_clickable_area_new(
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_t *on_click);
