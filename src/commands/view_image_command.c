#include "index.h"
#include "../image_viewer/index.h"

static int run(char **args, const commander_t *commander);

void
view_image_command(const commander_t *commander) {
    command_t *command = command_new("view-image");
    command->description = "view .icn or .chr image";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args, const commander_t *commander) {
    (void) commander;

    char **paths = args + 1;
    char *path = paths[0];

    image_viewer_t *image_viewer = image_viewer_new(path);
    image_viewer_open(image_viewer);
    image_viewer_destroy(&image_viewer);

    return 0;
}
