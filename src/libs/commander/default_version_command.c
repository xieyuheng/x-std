#include "index.h"

static int run(char **args, const commander_t *commander);

void
default_version_command(const commander_t *commander) {
    command_t *command = command_new("version");
    command->description = "print version";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args, const commander_t *commander) {
    (void) args;

    printf("%s\n", commander->version);

    return 0;
}
