#include "index.h"
#include "../example_button/index.h"
#include "../example_blending/index.h"

static int run(commander_t *commander);

void
edit_command(commander_t *commander) {
    command_t *command = command_new("edit");
    command->description = "edit a .hex font file";
    command->run = run;
    commander_add(commander, command);
}

int
run(commander_t *commander) {
    (void) commander;
    printf("[edit] todo\n");
    return 1;
}
