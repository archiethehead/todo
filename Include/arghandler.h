#include <plan.h>

#pragma once 

#ifndef ARGHANDLER_H
#define ARGHANDLER_H

typedef struct argcommandstruct {

    // metadata
    char* name;
    char* margs;
    char* oargs;
    char* description;
    void (*fptrs)(int* argc, char** argv);


} argcommand;

extern const argcommand argcommands[];

extern const int commandcount;

extern void toLower(char* string);

#endif //ARGHANDLER_H
