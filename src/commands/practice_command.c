#include "index.h"
#include "../button_practice/index.h"

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
    char **names = args + 1;
    char *name = names[0];

    if (string_equal(name, "button")) {
        button_practice_start();
        return 0;
    }

    fprintf(stderr, "[practice] unknown practice name: %s\n", name);
    fprintf(stderr, "[practice] known practices: "
            "button"
            "\n");
    return 1;
}
