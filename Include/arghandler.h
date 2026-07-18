#ifndef ARGHANDLER_H
#define ARGHANDLER_H

#include <plan.h>

#define strequal(x, y) !(strcmp(x, y))

typedef struct argcommandstruct {

    char* name;
    char* description;
    void (*fptrs)(int argc, char** argv);

} argcommand;

extern const argcommand argcommands[];

extern const int commandcount;

extern int verbose;

extern void toLower(char* string);

#endif //ARGHANDLER_H
