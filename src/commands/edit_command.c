#include "index.h"
#include "../editor/index.h"

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
    editor_start();
    return 1;
}
