#include "headers.h"

void command_jobs(char *token[], int num_arg)
{
    if (num_arg > 2)
    {
        printf("ERROR: jobs: too many arguments\n");
        return;
    }
    int flag_r = 1;
    int flag_s = 1;
    if (num_arg == 2)
    {
        flag_r = 0;
        flag_s = 0;
        if (strcmp(token[1], "-r") == 0)
        {
            flag_r = 1;
        }
        else if (strcmp(token[1], "-s") == 0)
        {
            flag_s = 1;
        }
        else
        {
            printf("ERROR: jobs: invalid option --'%s'\n", token[1]);
        }
    }
    for (int i = 0; i < background_index; i++)
    {
        char stat_info[1024];
        sprintf(stat_info, "/proc/%d/stat", bp[i].pid);
        FILE *stat_file = fopen(stat_info, "r");
        if (stat_file == NULL)
        {
            printf("ERROR: jobs: cannot open stats file '%s' for '%s'\n", stat_info, bp[i].process_name);
        }
        else
        {
            char buffer[1024];
            char state[3];
            char pid[12];
            for (int i = 1; fscanf(stat_file, "%s", buffer) == 1; i++)
            {
                if (i == 1)
                {
                    strcpy(pid, buffer);
                }

                if (i == 3)
                {
                    strcpy(state, buffer);
                    break;
                }
            }

            if (flag_s == 1 && strcmp(state, "T") == 0)
            {
                printf("[%d] Stopped %s [%s]\n", bp[i].job_num + 1, bp[i].process_name, pid);
            }

            else if (flag_r == 1 && strcmp(state, "T") != 0)
            {
                printf("[%d] Running %s [%s]\n", bp[i].job_num + 1, bp[i].process_name, pid);
            }
        }
    }
    return;
}