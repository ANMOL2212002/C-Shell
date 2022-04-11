#include "headers.h"

void command_pinfo(char *token[], int num)
{
    if (num > 2)
    {
        printf("ERROR: pinfo: too many arguments\n");
        return;
    }
    char stat_info[1024];
    char stat_exe[1024];
    if (token[1] != NULL)
    {
        sprintf(stat_info, "/proc/%s/stat", token[1]);
        sprintf(stat_exe, "/proc/%s/exe", token[1]);
    }
    else
    {
        int pid;
        pid = getpid();
        sprintf(stat_info, "/proc/%d/stat", pid);
        sprintf(stat_exe, "/proc/%d/exe", pid);
    }
    FILE *f_stat = fopen(stat_info, "r");
    if (f_stat == NULL)
    {
        printf("ERROR: pinfo: Process does not exist");
        return;
    }
    char state[3];
    char buffer[1024];
    char tpgid[20];
    char pgrp[20];

    for (int i = 1; fscanf(f_stat, "%s", buffer) == 1; i++)
    {
        if (i == 1)
        {
            printf("pid -- %s\n", buffer);
        }
        else if (i == 3)
        {
            printf("Process Status -- %s", buffer);
            strcpy(state, buffer);
        }
        else if (i == 5)
        {
            strcpy(pgrp, buffer);
        }
        else if (i == 8)
        {
            strcpy(tpgid, buffer);
            if (strcmp(tpgid, pgrp) == 0 && (state[0] == 'R' || state[0] == 'S'))
            {
                printf("+");
            }
            printf("\n");
        }
        else if (i == 23)
        {
            printf("memory -- %s {Virtual Memory}\n", buffer);
        }
    }
    fclose(f_stat);
    char exe_path[1024];
    int t = readlink(stat_exe, exe_path, 1000);
    if (t < 0)
    {
        perror("Error: reading the path to executable");
    }
    else
    {
        printf("Executable Path -- ");
        exe_path[t] = '\0';
        char *ptr = exe_path;
        int home_length = strlen(ptr_to_home);
        for (int i = 0; i < home_length; i++, ptr++)
        {
            if (home_directory[i] != exe_path[i])
            {
                printf("%s\n", exe_path);
                break;
            }
            else if (i == home_length - 1)
            {
                ptr++;
                printf("~%s\n", ptr);
            }
        }
    }
    return;
}
