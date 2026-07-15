#include <binfile.h>

#define TEXT_SIZE 64
#define FILE_NAME "Tasks.bin" 

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

void initBinFile() {

    FILE *fptr;
    fptr = fopen(FILE_NAME, "w");
    fclose(fptr);

}
