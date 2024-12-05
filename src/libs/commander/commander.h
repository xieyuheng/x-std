#pragma once

typedef void (commander_plugin_t)(const commander_t *commander);

struct commander_t {
    const char *name;
    const char *version;
    const char *description;
    int argc;
    char **argv;
    list_t *command_list;
};

commander_t *commander_new(
    const char *name,
    const char *version,
    int argc,
    char **argv);
void commander_destroy(commander_t **self_pointer);

void commander_add(const commander_t *self, command_t *command);
void commander_use(const commander_t *self, commander_plugin_t *plugin);
void commander_help(const commander_t *self);
int commander_run(const commander_t *self);
