#include <stdlib.h>
#include <plan.h>
#define strequal(x, y) !(strcmp(x, y))

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

        if(strequal(argcommands[i].shortname, argv[1]) || strequal(argcommands[i].longname, argv[1])){
            
            printf("%s \n%s \n%s \n", (argcommands[i].shortname), (argcommands[i].longname), (argv[1]));
            printf("Equal");

        };

    }
    
    return 0;

}
