#include <stdlib.h>
#include <arghandler.h>
#include <plan.h>
#define strequal(x, y) !(strcmp(x, y))

int main(int argc, char* argv[]) {

    if (!argc) return 1;

    for (int i = 0; i < argc; i++) {

        toLower(argv[i]);

    }    

    for (int i = 0; i < commandcount; i++) {

        if(strequal(argcommands[i].name, argv[1])){

            argcommands[i].fptrs(&argc, argv);            

        };

    }
    
    return 0;

}
