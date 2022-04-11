#include "headers.h"

void ctrl_c()
{
    pid_t pid = getpid();
    printf("\n");
    if (pid == shell_pid)
    {
        if (forgnd_id != -1)
        {
            if (kill(forgnd_id, SIGINT) != 0)
            {
                perror("ERROR : ctrl-c (kill)");
            }
        }
        else
        {
            prompt();
        }
    }
    else
    {
        prompt();
    }
    fflush(stdout);
    return;
}

void ctrl_z()
{
    pid_t pid = getpid();
    printf("\n");
    if (pid == shell_pid)
    {
        if (forgnd_id != -1)
        {
            if (kill(forgnd_id, SIGTSTP) != 0)
            {
                perror("ERROR : ctrl-z (kill)");
            }
            bp[background_index].pid = forgnd_id;
            strcpy(bp[background_index].process_name, forgnd_name);
            bp[background_index].job_num = job_index;
            job_index++;
            background_index++;
            qsort(bp, background_index, sizeof(bp[0]), string_comparator);
        }
        else
        {
            prompt();
        }
    }
    else
    {
        prompt();
    }
    fflush(stdout);
    return;
}
