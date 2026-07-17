#include <arghandler.h>

const argcommand argcommands[] =    {

                                    {"help",    "[command name(s)] Outputs the details of a command(s) this program can execute", &help},
                                    {"newtodo", "<-n name> [-c category, -d dd-mm-yy, -t hh:mm -a assignee] writes a task to the database according to your input value(s)", &newtask},
                                    {"todoout","[-f status] outputs all of the tasks saved to file according to the optionally specified filter.", &outputTasks},
                                    {"edit", "temp", &editTask}

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
