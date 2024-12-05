#include "index.h"
#include "../editor/index.h"

static int run(char **args);

void
self_test_command(const commander_t *commander) {
    command_t *command = command_new("self-test");
    command->description = "run self test";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args) {
    (void) args;

    printf("<self-test>\n");

    libs_test();
    editor_test();

    printf("</self-test>\n");

    return 0;
}
