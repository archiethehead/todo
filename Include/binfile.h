#ifndef BINFILE_H
#define BINFILE_H

#include <stdio.h>
#include <time.h>

#define TEXT_SIZE 64

// Definitions for thes states of
// the task struct state flag.
#define FREE 0
#define TAKEN 1
#define COMPLETED 2
#define OVERDUE 3

#pragma pack(push, 1)

typedef struct {

    unsigned char status;
    unsigned short id;
    time_t timestamp;
    char title[TEXT_SIZE];
    char assignee[TEXT_SIZE];
    char category[TEXT_SIZE];

} Task;

#pragma pack(pop)

extern void initBinFile();
extern void addTaskToFile(Task newTask);
extern void outputAlltasks();
extern int verbose;

#endif
