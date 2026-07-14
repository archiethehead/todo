#include <arghandler.h>
#include <plan.h>
#include <stdio.h>

#define EMPTY "NONE"

void help(int* argc, char** argv) {

    puts("\nCOMMANDS\n--------\n\n<> = Mandatory Argument(s)\n[] = Optional Argument(s)\nArguments are not case-sensitive.\nArguments are order-sensitive.\n");

    
    char arrow[] = "--->";

    if (*argc == 3) {

        for (int i = 0; i < commandcount; i++) {

           if (strequal(argv[2], argcommands[i].name)) {

                printf("%-8s %s %s\n", argcommands[i].name, arrow, argcommands[i].description);
                
                return;

            } 
    
        }
        
        printf("ERROR ---> Unrecognised command name :(");
        return;

    }

    for (int i = 0; i < commandcount; i++) {
        
        printf("%-8s %s %s\n", argcommands[i].name, arrow, argcommands[i].description);
        

    }

    puts("\n");

};
