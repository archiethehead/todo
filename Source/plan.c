#include <arghandler.h>
#include <plan.h>
#include <stdio.h>

#define EMPTY "NONE"

void newtask(int argc, char** argv) {

    int c;
    char* taskName = NULL;
    char* taskCategory;

}

void help(int argc, char** argv) {

    puts("\nCOMMANDS\n--------\n\n<> = Mandatory Argument(s)\n[] = Optional Argument(s)\nArguments are not case-sensitive.\nArguments are order-sensitive.\n");
    
    char error[] = "ERROR";

    if (argc > 2) {

        for (int j = 2; j < argc; j++) {

            int argfound = 0;

            for (int i = 0; i < commandcount; i++) {

               if (strequal(argv[j], argcommands[i].name)) {

                    printf("%-8s ---> %s\n", argcommands[i].name, argcommands[i].description);
                    argfound ^= 1;
                    break;                              
    
                } 
        
            }
            
            if (!argfound) {
                
                printf("%-8s ---> %s is an unrecognised command name :(\n", error, argv[j]);
            
            }

        }
            
    }

    else {

        for (int i = 0; i < commandcount; i++) {
            
            printf("%-8s ---> %s\n", argcommands[i].name, argcommands[i].description);
            
        }

    }

    puts("\n");
    return;

};
