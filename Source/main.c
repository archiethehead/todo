#include <stdlib.h>
#include <time.h>
#include <cjson/cjson.h>

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

    for (int i = 0; i < commandcount; i++) {
            
        if (!(strcmp(argcommands[i].shortname, argv[1])) || !(strcmp(argcommands[i].longname, argv[1]))) {

            argcommands[i].fptrs(argv);

        }
    
    }

    printf("hello world");
    return 0;

}
