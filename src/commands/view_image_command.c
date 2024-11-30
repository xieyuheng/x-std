#include "index.h"

static int run(char **args);

void
view_image(const commander_t *commander) {
    command_t *command = command_new("view-image");
    command->description = "view .icn or .chr image";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args) {
    char **paths = args + 1;
    char *path = paths[0];

    canvas_t *canvas = canvas_new(0x10 * 8, 0x10 * 8);
    canvas_window_t *canvas_window = canvas_window_new(canvas, 8);
    canvas_window->title = "hello canvas";
    file_t *file = file_open_or_fail(path, "rb");
    uint8_t *bytes = file_read_bytes(file);
    canvas_draw_chr(canvas, 0, 0, bytes, 0x10, 0x10, 1);
    // canvas_draw_icn(canvas, 0, 0, bytes, 0x10, 0x10, 1);
    canvas_window_open(canvas_window);

    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);

    return 0;
}
