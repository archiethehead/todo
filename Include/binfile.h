#ifndef BINFILE_H
#define BINFILE_H

#include <stdio.h>
#include <time.h>

#define TEXT_SIZE 64

extern void initBinFile();
extern int verbose;

#pragma pack(push, 1)

typedef struct {

    unsigned char free;
    unsigned short id;
    time_t timestamp;
    char title[TEXT_SIZE];
    char assignee[TEXT_SIZE];
    char category[TEXT_SIZE];

} Task;

#pragma pack(pop)

#endif
