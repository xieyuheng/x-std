#include "index.h"
#include "../practices/button_practice/index.h"

static int run(char **args);

void
practice_command(const commander_t *commander) {
    command_t *command = command_new("practice");
    command->description = "run practice programs";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args) {
    char **paths = args + 1;
    char *path = paths[0];

    if (string_equal(path, "button")) {
        button_practice();
        return 0;
    }

    return 0;
}
