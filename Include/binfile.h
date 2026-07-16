#ifndef BINFILE_H
#define BINFILE_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define TEXT_SIZE 64

// Definitions for thes states of
// the task struct state flag.
#define FREE 1
#define TAKEN 2
#define COMPLETED 3
#define OVERDUE 4

extern uint8_t idBitmap[1024];

#define SET_ID(id) (idBitmap[id >> 3] |= (1 << (id & 7)))
#define SET_ID(id) (idBitmap[id >> 3] |= (1 << (id & 7)))
#define UNSET_ID(id) (idBitmap[id >> 3] &= ~(1 << (id & 7)))

#pragma pack(push, 1)

typedef struct {

    uint8_t status;
    uint16_t id;
    time_t timestamp;
    char title[TEXT_SIZE];
    char assignee[TEXT_SIZE];
    char category[TEXT_SIZE];

} Task;

#pragma pack(pop)

extern void initBinFile();
extern void addTaskToFile(Task newTask);
extern void outputAlltasks();
extern void outputActivetasks();
extern int verbose;

#endif
