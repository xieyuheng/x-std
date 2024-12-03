#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(3 * TILE, 3 * TILE, 10);
    canvas_window_t *window = canvas_window_new(canvas);
    window->title = "hello canvas";

    // {
    //     for (size_t i = 0; i < 8; i++)
    //         canvas_draw_pixel(canvas, i, i, 1);
    //     canvas_window_open(window);
    // }

    // {
    //     canvas_fill_bottom_left(canvas, TILE, 2 * TILE, SL_COLOR);
    //     canvas_window_open(window);
    // }

    // {
    //     canvas_fill_top_right(canvas, TILE, 2 * TILE, SL_COLOR);
    //     canvas_window_open(window);
    // }

    // {
    //     canvas_fill_top_left(canvas, TILE, 2 * TILE, SL_COLOR);
    //     canvas_window_open(window);
    // }

    // {
    //     const char *file_name = "/home/xyh/projects/xieyuheng/bifer/src/practices/button10x10.chr";
    //     file_t *file = fopen(file_name, "rb");
    //     uint8_t *bytes = file_read_bytes(file);
    //     uint8_t *button_up_chr = chr_subimage(bytes, 0x10, 0, 0, 3, 3);
    //     canvas_draw_chr(canvas, 0, 0, button_up_chr, 3, 3, 1);
    //     // uint8_t *button_down_chr = chr_subimage(bytes, 0x10, 3, 0, 3, 3);
    //     // canvas_draw_chr(canvas, 0, 0, button_down_chr, 3, 3, 1);
    //     canvas_window_open(window);
    // }

    canvas_window_destroy(&window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
