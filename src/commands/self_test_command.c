#include "index.h"
#include "../editor/index.h"

static int run_with_commander(char **args, const commander_t *commander);

void
self_test_command(const commander_t *commander) {
    command_t *command = command_new("self-test");
    command->description = "run self test";
    command->run_with_commander = run_with_commander;
    commander_add(commander, command);
}

int
run_with_commander(char **args, const commander_t *commander) {
    (void) commander;
    (void) args;

    printf("<self-test>\n");

    libs_test();
    editor_test();

    printf("</self-test>\n");

    return 0;
}
