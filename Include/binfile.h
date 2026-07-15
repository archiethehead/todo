#include <stdio.h>

#ifndef BINFILE_H
#define BINFILE_H

#define TEXT_SIZE 64

extern void initBinFile();

#pragma pack(push, 1)

typedef struct {

    unsigned char free;
    unsigned short id;
    unsigned long timestamp;
    char title[TEXT_SIZE];
    char assignee[TEXT_SIZE];
    char category[TEXT_SIZE];

} Task;

#pragma pack(pop)


#endif
