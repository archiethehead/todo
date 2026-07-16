#ifndef PLAN_H
#define PLAN_H

#include <arghandler.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt/getopt.h>

void help(int argc, char** argv);
void newtask(int argc, char** argv);
void outputTasks(int argc, char** argv);

typedef struct {

    char* str;
    uint8_t num;

} strarg;

#endif //PLAN_H
