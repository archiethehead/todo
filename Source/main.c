#include <stdio.h>
#include <signal.h>
#include <arghandler.h>
#include <plan.h>
#include <binfile.h>

int recognisedCommand = 0;
int verbose = 0;
extern int writing;

void sigintHandler(int intcode)  {

    if (writing) {

        printf("Interrupt ignored ---> Program is writing to file\n");
        return;

    }

    printf("Program interrupted by sigint, exiting . . .\n");
    exit(0);

};

int main(int argc, char* argv[]) {

    sigintHandler(3);

    signal(SIGINT, &sigintHandler);

    if (argc == 1) {

        help(argc, argv);
        return -1;

    }


    for (int i = 1; i < argc; i++) {
    
        if (strequal(argv[i], "-v")) {
    
            verbose = 1;
            break;
        
        }
    
    }   
 
    
    FILE *fp = fopen("Tasks.bin", "r");
    if (!fp) {

        initBinFile();      

    }

    else {

        fclose(fp);

    }
 
    updateBinFile();

    for (int i = 0; i < commandcount; i++) {
    
        if(strequal(argcommands[i].name, argv[1])){

            argcommands[i].fptrs(argc, argv);            
            recognisedCommand = 1;

        };

    }

    if (!recognisedCommand) {

        printf("ERROR ---> %s is not a recognised command :(\nTry 'todo help.\n'", argv[1]);
        return -1;

    }

    puts("\n");
    
    return 0;

}
