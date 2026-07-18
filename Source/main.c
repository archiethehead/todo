#include <stdio.h>
#include <arghandler.h>
#include <plan.h>
#include <binfile.h>

int verbose = 0;

int main(int argc, char* argv[]) {


    for (int i = 1; i < argc; i++) {
    
        if (strequal(argv[i], "-v")) {
    
            verbose = 1;
            break;
        
        }
    
    }   
 
    
    if (!argc) return 1;

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

        };

    }
    
    return 0;

}
