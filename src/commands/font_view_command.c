#include "index.h"
#include "../font_viewer/index.h"

static int run(commander_t *commander);

void
font_view_command(commander_t *commander) {
    command_t *command = command_new("font:view");
    command->description = "edit a .hex font file";
    command->run = run;
    commander_add(commander, command);
}

int
run(commander_t *commander) {
    (void) commander;
    font_viewer_start();
    return 1;
}
