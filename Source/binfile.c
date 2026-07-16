#include <stdio.h>
#include <binfile.h>

#define FILE_NAME "Tasks.bin"
#define fileNotOpenedError printf("%s", fileNotOpened)

char fileNotOpened[] = "ERROR ---> Tasks file could not be opened :(";

void initBinFile() {

    FILE* fileptr;
    fileptr = fopen(FILE_NAME, "w");
    fclose(fileptr);

}

int getBinFileSize() {

    FILE* fileptr = fopen(FILE_NAME, "rb");
    
    if (!fileptr) {

        fileNotOpenedError;
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
    
    if (!fileptr) {

        fileNotOpenedError;

    }
    
    for (int i = 0; i < size; i++) {
        
        int offset = i * sizeof(Task);
        fseek(fileptr, offset, SEEK_SET);
        unsigned char flag;
        fread(&flag, sizeof(flag), 1, fileptr);
        
        if (!flag) {

            fseek(fileptr, offset, SEEK_SET);
            
            if (verbose) {

                printf("\nOverwriting at free position %d", ftell(fileptr));

            }            
           
             fwrite(&newTaskStruct, sizeof(Task), 1, fileptr);
            fclose(fileptr);
            return;            

        }

    }

    fseek(fileptr, 0L, SEEK_END);
    
    if (verbose) {
    
        printf("\nWriting at position %d", ftell(fileptr));

    }

    fwrite(&newTaskStruct,  sizeof(Task), 1, fileptr);
    fclose(fileptr);
    return;

}

void outputAllTasks() {
    
    printf("\n-----\nTASKS\n-----\n\n");

    int size = getBinFileSize();
    FILE* fileptr = fopen(FILE_NAME, "r+b");
    
    if (!fileptr) {

        fileNotOpenedError;

    }

    
    for (int i = 0; i < size; i++) {
        
        int offset = i * sizeof(Task);
        fseek(fileptr, offset, SEEK_SET);
        
        Task taskBuff;
        fread(&taskBuff, sizeof(taskBuff), 1, fileptr);

        printf("%s\nCategory --> %s \nAssignee --> %s \nDeadline --> %s\n",
                taskBuff.title, taskBuff.category, taskBuff.assignee, ctime(&taskBuff.timestamp));


    }

    return;

}
