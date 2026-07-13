#include <stdio.h>
#include <time.h>
#include <cjson/cjson.h>

extern int __cdecl strequal(char* command, char* userin);

typedef struct argcommandstruct {

    char* shortname;
    char* longname;
    void (*fptrs)(char* argv[]);

} argcommand;


void help(char* argv[]) {

    printf("helped!");

}

const argcommand argcommands[] =    {
                                    
                                    {"-h","--help", &help},
                                    {"test","testt", &help}
                                    
                                    };

const int commandcount = sizeof(argcommands) / sizeof(argcommand);

int main(int argc, char* argv[]) {

    if (!argc) return 1;

    if(strequal("-h", "-h")){

        printf("Equal");

    };
    
    return 0;

}
