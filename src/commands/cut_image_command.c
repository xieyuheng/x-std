#include "index.h"
#include "../editor/index.h"

static int run_with_commander(char **args, const commander_t *commander);

void
cut_image_command(const commander_t *commander) {
    command_t *command = command_new("cut-image");
    command->description = "cut subimage from .chr image";
    command->run_with_commander = run_with_commander;
    commander_add(commander, command);
}

int
run_with_commander(char **args, const commander_t *commander) {
    char *input_path = args[0];
    char *x_string = args[1];
    char *y_string = args[2];
    char *output_path = args[3];

    printf("[cut_image_command] argc: %d\n", commander->argc);
    printf("[cut_image_command] input_path: %s\n", input_path);
    printf("[cut_image_command] x_string: %s\n", x_string);
    printf("[cut_image_command] y_string: %s\n", y_string);
    printf("[cut_image_command] output_path: %s\n", output_path);

    return 0;
}
