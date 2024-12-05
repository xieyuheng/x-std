#include "index.h"
#include "../editor/index.h"

static int run(char **args);

void
cut_image_command(const commander_t *commander) {
    command_t *command = command_new("cut-image");
    command->description = "cut subimage from .chr image";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args) {
    (void) args;

    printf("[cut_image_command]\n");

    return 0;
}
