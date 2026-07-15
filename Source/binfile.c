#include <stdio.h>
#include <binfile.h>

#define FILE_NAME "Tasks.bin"


void initBinFile() {

    FILE* fileptr;
    fileptr = fopen(FILE_NAME, "w");
    fclose(fileptr);

}

int getBinFileSize() {

    FILE* fileptr = fopen(FILE_NAME, "rb");
    
    if (!fileptr) {

        printf("ERROR ---> Tasks file could not be found :(");
        return -1;

    }

    fseek(fileptr, 0L, SEEK_END);
    long int size = ftell(fileptr);
    size = size / sizeof(Task);
    return size;

}

void addTaskToFile(Task newTaskStruct) {

    int size = getBinFileSize();
    FILE* fileptr = fopen(FILE_NAME, "r+b");
    
    for (int i = 0; i < size; i++) {
        
        int offset = i * sizeof(Task);
        fseek(fileptr, offset, SEEK_SET);
        unsigned char flag;
        fread(&flag, sizeof(flag), 1, fileptr);
        
        if (flag) {
            
            fseek(fileptr, offset, SEEK_SET);
            fwrite(&newTaskStruct, sizeof(Task), 1, fileptr);
            printf("a");
            fclose(fileptr);
            return;            

        }

    }

    printf("Writing at position %d", ftell(fileptr));

    

    fseek(fileptr, 0L, SEEK_END);
    fwrite(&newTaskStruct,  sizeof(Task), 1, fileptr);
    fclose(fileptr);
    return;

}
