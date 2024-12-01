#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(3, 3);
    canvas_window_t *window = canvas_window_new(canvas, 20);
    window->title = "hello canvas";

    // {
    //     for (size_t i = 0; i < 8; i++)
    //         canvas_draw_pixel(canvas, i, i, 1);
    //     canvas_window_open(window);
    // }

    canvas_window_destroy(&window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
