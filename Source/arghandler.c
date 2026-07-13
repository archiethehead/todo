#include <arghandler.h>

#define EMPTY "None"

const argcommand argcommands[] =    {

                                    {"help", EMPTY, "Command Name", "Outputs the details of a command(s) this program can execute", &help},

                                    };

const int commandcount = sizeof(argcommands) / sizeof(argcommand);

void toLower(char* string) {

    int len = strlen(string);
    
    for (int i = 0;  i < len; i++) {

        if(string[i] > 64 && string[i] < 91) {

            string[i] += 32;

        }
    
    }

}
