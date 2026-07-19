#ifndef PLAN_H
#define PLAN_H

#include <arghandler.h>
#include <binfile.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <getopt/getopt.h>

// Do NOT change this, this prevents Linux builds
// from linking the stdlib version of getopt,  which
// doesn't behave how the program expects our version
// of getopt to behave.
// 
// |
// |
// |
// V

#define getopt winGetopt
#define VERSION "1.2.0"

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
