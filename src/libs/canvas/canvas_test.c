#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(0x10, 0x10);
    canvas_window_t *canvas_window = canvas_window_new(canvas, 8);
    canvas_window->title = "hello canvas";

    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
