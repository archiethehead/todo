#include <binfile.h>

#define FILE_NAME "Tasks.bin"
#define fileNotOpenedError printf("%s", fileNotOpened)

char fileNotOpened[] = "ERROR ---> Tasks file could not be opened :("; 

uint8_t idBitmap[1024] = {0};
int idCount = 0;

void initBinFile() {

    FILE* fileptr;
    fileptr = fopen(FILE_NAME, "w");
    fclose(fileptr);
    return;

}

void updateBinFile() {

    int size = getBinFileSize();

    if (size == -1) return;
   
    Task* taskFileBuffer = (Task*)malloc(sizeof(Task) * size);    
    
    FILE* fileptr = fopen(FILE_NAME, "r+b");

    if (!fileptr) {

        fileNotOpenedError;
        return;

    }

    fseek(fileptr, 0, SEEK_SET);
    fread(taskFileBuffer, sizeof(Task), size, fileptr);

    time_t seconds;
    time(&seconds);

    for (int i = 0; i < size; i++) {

        uint8_t status = taskFileBuffer[i].status;
        time_t taskTime = taskFileBuffer[i].timestamp;

        if (status == 2 && taskTime < seconds) {

            status = OVERDUE;
            taskFileBuffer[i].status = OVERDUE;
            int offset = (i * sizeof(Task)) + OFFSET(Task, status);
            fseek(fileptr, offset, SEEK_SET);
            fwrite(&status,  sizeof(status), 1, fileptr);

        }

    }

    fclose(fileptr);
    free(taskFileBuffer);
    return;    

}

int getBinFileSize() {

    FILE* fileptr = fopen(FILE_NAME, "rb");
    
    if (!fileptr) {

        fileNotOpenedError;
        return -1;

    }

    fseek(fileptr, 0, SEEK_END);
    long int size = ftell(fileptr);
    size = size / sizeof(Task);
    fclose(fileptr);
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
        Task taskBuff;
        fread(&taskBuff, sizeof(Task), 1, fileptr);
        
        if (taskBuff.status == 1) {
   
            newTaskStruct.id = taskBuff.id;
            fseek(fileptr, offset, SEEK_SET);
            
            if (verbose) {
                
                printf("\nReusing id 0x%x", taskBuff.id);
                printf("\nOverwriting at free position %d", ftell(fileptr));

            }            
            
            fwrite(&newTaskStruct, sizeof(Task), 1, fileptr);
            fclose(fileptr);
            return;            

        }

    }

    fseek(fileptr, 0L, SEEK_END);
    
    if (verbose) {
    
        printf("\nWriting at position 0x%x", ftell(fileptr));

    }

    fwrite(&newTaskStruct,  sizeof(Task), 1, fileptr);
    fclose(fileptr);
    return;

}

void outputAllTasks(char* status, uint8_t flag) {
    
    printf("\n\n%s tasks:\n", status);

    int size = getBinFileSize();
    FILE* fileptr = fopen(FILE_NAME, "r+b");
    
    if (!fileptr) {

        fileNotOpenedError;

    }

    
    for (int i = 0; i < size; i++) {
        
        int offset = i * sizeof(Task);
        fseek(fileptr, offset, SEEK_SET);
        
        if (verbose) {

            printf("\n\nReading at position 0x%x", ftell(fileptr));

        }

        Task taskBuff;
        fread(&taskBuff, sizeof(taskBuff), 1, fileptr);

        if (!((taskBuff.status == flag) || (!flag))) {

            continue;

        }

        char status[11];

        switch(taskBuff.status) {

            case TAKEN:
                strcpy(status, "Active");
                break;

            case COMPLETED:
                strcpy(status, "Completed");
                break;

            case OVERDUE:
                strcpy(status, "Overdue");
                break;
    
            case INDEFINITE:
                strcpy(status, "Indefinite");
                break;

        }

        char time[20];     

        if (taskBuff.timestamp > 0) {

            strcpy(time, ctime(&taskBuff.timestamp));    

        }

        else {

            strcpy(time, "N/A\n");

        }

        printf("\n\n%s\nID --> %d \nCategory --> %s \nAssignee --> %s \nDeadline --> %sStatus   --> %s",
                taskBuff.title, taskBuff.id, taskBuff.category, taskBuff.assignee, time, status);

    }

    fclose(fileptr);
    return;

} 

