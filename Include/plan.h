#ifndef PLAN_H
#define PLAN_H

#include <arghandler.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <getopt/getopt.h>

#define VERSION "1.0.0"

extern void help(int argc, char** argv);
extern void newtask(int argc, char** argv);
extern void editTask(int argc, char** argv);
extern void changeTaskStatus(int argc, char** argv);
extern void outputTasks(int argc, char** argv);
extern void version(int argc, char** argv);

extern int verbose;

typedef struct {

    char* str;
    uint8_t num;

} strarg;

#endif //PLAN_H
