#include <arghandler.h>
#include <plan.h>
#include <stdio.h>

#define EMPTY "NONE"

void help(int* argc, char** argv) {

    puts("\nCOMMANDS\n--------\n\nM = Mandatory Argument, O = Optional Argument\nArguments are not case-sensitive.\n");

    for (int i = 0; i < commandcount; i++) {

        printf("%-8s M: %-20s O: %-20s --> %s\n", argcommands[i].name, argcommands[i].margs, argcommands[i].oargs, argcommands[i].description);

    }

    puts("\n");

};
