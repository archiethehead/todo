#include <plan.h>

extern int verbose;

void newtask(int argc, char** argv) {

    int opt;
    uint8_t isDateSet = 0;
    char* taskName = NULL;
    char* taskAssignee = "Everyone";
    char* taskCategory = "N/A";
    time_t raw_time = time(NULL);
    struct tm time = *(localtime(&raw_time));
    
    time.tm_isdst = -1;

    argv += 2;
    argc -= 2;

    optind = 0;    

    char* args[] = {"task", "help", "newtodo"};

    while((opt = getopt(argc, argv, "n:c::d:t::a::v")) != -1) {

        VOUT_("Parsing %c as %s\n", opt, optarg);
        
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

        epochTime = mktime(&time);
        newTaskStruct.status = TAKEN;

    }

       
    VOUT_("\nArguments parsed:\nName -> %s \nAssignee -> %s \nCategory -> %s \nDeadline -> %s", taskName, taskCategory, taskAssignee, ctime(&epochTime));

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
    char* category = NULL;
    char* assignee = NULL;

	argv += 2;
    argc -= 2;

	optind = 0;

    char* args[] = {"task", "help", "todoout"};

    while((opt = getopt(argc, argv, "f::c::a::v")) != -1) {

		if (optind == 1) {

			continue;

		}
 
        VOUT_("Parsing %c as %s\n", opt, optarg);
        
        switch(opt) {

            case 'f':

                if (optarg) {

                    filter = optarg;

                }
                
                break;

            case 'c':
                
                if (optarg) {

                    category = optarg;
    
                }

                break;

            case 'a':

                if (optarg) {

                    assignee = optarg;

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
    
        outputAllTasks("Active", 2, category, assignee);
        outputAllTasks("Overdue", 4, category, assignee);   
        return;        

    } 


    toLower(filter);
    
    if(filter[0] > 96 && filter[0] < 123) {

            filter[0] -= 32;

    }
    
    for (int i = 0; i < 6; i++) {

        if(strequal(filter, outputArgs[i].str)) {

            outputAllTasks(outputArgs[i].str, outputArgs[i].num, category, assignee);
            return;

        }

    }
    
    printf("ERROR ---> Invalid filter argument :(");
    help(3, args);
    return;

}

void editTask(int argc, char** argv) {

    int opt;
    int id = atoi(argv[2]);
    uint8_t isDateSet = 0;
    time_t raw_time = time(NULL);
    struct tm time = *(localtime(&raw_time));
    
    time.tm_isdst = -1;

    if (!(strequal(argv[2], "0")) && id == 0) {

        printf("ERROR ---> Character found where integer was expected :(");
        return;

    }

    Task editTaskDetails;
    int success = getTaskByID(id, &editTaskDetails); 

    if (!success) {

        printf("ERROR ---> Invalid id entered :(");
        return;

    }

    argv += 3;
    argc -= 3;

    optind = 0;    

    char* args[] = {"task", "help", "newtodo"};

    while((opt = getopt(argc, argv, "n::c::d:t::a::v")) != -1) {
   
        VOUT_("Parsing %c as %s\n", opt, optarg);
        
        switch(opt) {

            case 'n':

                if (optarg) {

                    strcpy(editTaskDetails.title, optarg);

                }

                break;
            
            case 'c':
            
                if (optarg) {
                    
                    strcpy(editTaskDetails.category, optarg);
                
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

                    isDateSet = 1;
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

                    strcpy(editTaskDetails.assignee, optarg);

                }
                break;

            case '?':
                help(3, args);
                return;

        }

    }

    if (isDateSet) {

        editTaskDetails.timestamp = mktime(&time);

        if (editTaskDetails.status != 3) {

            editTaskDetails.status = 2;

        }
        

    }
    
    saveTaskByID(id, editTaskDetails);

    return;
};

void changeTaskStatus(int argc, char** argv) {

    toLower(argv[1]);
    int id = atoi(argv[2]);
    uint8_t status;    

    if (strequal(argv[1], "done")) {

        status = COMPLETED;

    }

    else if (strequal(argv[1], "delete")) {

        status = FREE;

    }

    else if (strequal(argv[1], "redo")) {

        status = TAKEN;

    }

    else if (strequal(argv[1], "indef")) {


        status = INDEFINITE;

    }

    if (!(strequal(argv[2], "0")) && id == 0) {

        printf("ERROR ---> Character found where integer was expected :(");
        return;

    }

    Task editTaskBuffer;
    int success = getTaskByID(id, &editTaskBuffer);
    
    if (!success) {

        printf("ERROR ---> Invalid id entered :(");
        return;

    }

    editTaskBuffer.status = status;
    
    saveTaskByID(id, editTaskBuffer);

    return;

};

void help(int argc, char** argv) {

    puts("\nCOMMANDS\n--------\n\n<> = Mandatory Argument(s)\n[] = Optional Argument(s)\nArguments are case-sensitive\nArguments are not order-sensitive if specified with a -flag\n");
    
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

void version(int argc, char** argv) {

    printf("\nTODO Version %s\n", VERSION);

}
