#include <stdlib.h>
#include <arghandler.h>
#include <plan.h>
#include <binfile.h>

int main(int argc, char* argv[]) {
    
    if (!argc) return 1;

    updateBinFile();

    FILE *fp = fopen("Tasks.bin", "r");
    if (!fp) {

        initBinFile();        

    }

    else {

        fclose(fp);

    }
 
    for (int i = 0; i < commandcount; i++) {
    
        if(strequal(argcommands[i].name, argv[1])){

            argcommands[i].fptrs(argc, argv);            

        };

    }
    
    return 0;

}
