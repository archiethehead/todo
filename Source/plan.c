#include <plan.h>
#include <binfile.h>
#include <arghandler.h>

int verbose = 0;

extern char *optarg;
extern int optind;

void newtask(int argc, char** argv) {

    int opt;
    uint8_t isDateSet = 0;
    char* taskName = NULL;
    char* taskAssignee = "Everyone";
    char* taskCategory = "N/A";
    struct tm time = {0};
    
    time.tm_isdst = -1;

    argv += 2;
    argc -= 2;

    optind = 0;    

    char* args[] = {"task", "help", "newtodo"};

    while((opt = getopt(argc, argv, "n:c::d:t::a::v")) != -1) {

        if (verbose) {
    
            printf("Parsing %c as %s\n", opt, optarg);

        }
        
        switch(opt) {

            case 'n':

                if (optarg) {

                    taskName = optarg;

                }

                break;
            
            case 'c':
            
                if (optarg) {
                    
                    taskCategory = optarg;
                
                }

                break;

            case 'd':
                
                int year, month, day;
                if(sscanf(optarg, "%d-%d-%d", &day, &month, &year) == 3) {
                    
                    isDateSet = 1;
                    time.tm_year = year - 1900;
                    time.tm_mon = month - 1;
                    time.tm_mday =  day;
                    break;

                }

                else {

                    printf("ERROR ---> Invalid date format entered, dd-mm-yyyy was expected :(");
                    return;
        
                }
                
            case 't':
                
                int hours, minutes;
                if (sscanf(optarg, "%d:%d", &hours, &minutes) == 2) {

                    time.tm_hour = hours;
                    time.tm_min = minutes;
                    break;

                }

                else {

                    printf("ERROR ---> Invalid time format entered, hh:mm was expected :(");                    
                    return;    

                }

            case 'a':

                if (optarg) {

                    taskAssignee = optarg; 

                }
                break;

            case 'v':
                verbose = 1;
                break;
            
            case '?':
                help(3, args);
                return;

        }

    }

    if (!taskName) {
        
        printf("ERROR ---> required argument (task name) not specified :(\n");
        help(3, args);
        return;

    }
    
    time_t epochTime = 0;
    Task newTaskStruct;
    newTaskStruct.status = INDEFINITE;

    if (isDateSet) {

        time_t epochTime = mktime(&time);
        newTaskStruct.status = TAKEN;

    }

    if (verbose) {
        
        printf("\nArguments parsed:\nName -> %s \nAssignee -> %s \nCategory -> %s \nDeadline -> %s", taskName, taskCategory, taskAssignee, ctime(&epochTime));

    }

    newTaskStruct.id = 0;
    newTaskStruct.timestamp = epochTime;
    strcpy(newTaskStruct.title, taskName);
    strcpy(newTaskStruct.assignee, taskAssignee);
    strcpy(newTaskStruct.category, taskCategory);
    addTaskToFile(newTaskStruct);   

    return;

}


strarg outputArgs[] =    {

                                {"Free", FREE},
                                {"Active", TAKEN},
                                {"Completed", COMPLETED},
                                {"Overdue", OVERDUE},
                                {"Indefinite", INDEFINITE},
                                {"*", ALL}

                         };

void outputTasks(int argc, char** argv) {

    
    int opt;
    char* filter = NULL;

    argv += 2;
    argc -= 2;

    optind = 0;    

    char* args[] = {"task", "help", "todoout"};

    while((opt = getopt(argc, argv, "f::v")) != -1) {

        if (verbose) {
    
            printf("Parsing %c as %s\n", opt, optarg);

        }
        
        switch(opt) {

            case 'f':

                if (optarg) {

                    filter = optarg;

                }
                
                break;

            case 'v':
                verbose = 1;
                break;
            
            case '?':
                help(3, args);
                return;

        }

    }

    if (filter == NULL) {
    
        outputAllTasks("Active", 2);
        outputAllTasks("Overdue", 4);   
        return;        

    } 


    toLower(filter);
    
    if(filter[0] > 96 && filter[0] < 123) {

            filter[0] -= 32;

    }
    
    for (int i = 0; i < 6; i++) {

        if(strequal(filter, outputArgs[i].str)) {

            outputAllTasks(outputArgs[i].str, outputArgs[i].num);
            return;

        }

    }
    
    printf("ERROR ---> Invalid filter argument :(");
    help(3, args);
    return;

}

void help(int argc, char** argv) {

    puts("\nCOMMANDS\n--------\n\n<> = Mandatory Argument(s)\n[] = Optional Argument(s)\nArguments are case-sensitive\nCommand arguments are not order-sensitive\n");
    
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

}
