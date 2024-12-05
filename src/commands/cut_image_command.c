#include "index.h"
#include "../editor/index.h"

static int run(commander_t *commander);

void
cut_image_command(commander_t *commander) {
    command_t *command = command_new("cut-image");
    command->description = "cut subimage from .chr image";
    command->run = run;
    commander_add(commander, command);
}

int
run(commander_t *commander) {
    char **argv = commander_rest_argv(commander);
    
    char *input_path = argv[0];
    char *x_string = argv[1];
    char *y_string = argv[2];
    char *output_path = argv[3];

    printf("[cut_image_command] argc: %d\n", commander->argc);
    printf("[cut_image_command] input_path: %s\n", input_path);
    printf("[cut_image_command] x_string: %s\n", x_string);
    printf("[cut_image_command] y_string: %s\n", y_string);
    printf("[cut_image_command] output_path: %s\n", output_path);

    return 0;
}
