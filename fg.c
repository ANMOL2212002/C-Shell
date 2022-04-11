#include "headers.h"

void command_fg(char *token[], int num_tok)
{
    if (num_tok == 2)
    {
        if (check_num(token[1]))
        {
            printf("ERROR: fg: given job number is not a valid number\n");
            return;
        }

        int fg_job_num = atoi(token[1]);
        char process_name[64];
        pid_t process_pid;
        for (int i = 0; i < background_index; i++)
        {
            if (fg_job_num - 1 == bp[i].job_num)
            {
                process_pid = bp[i].pid;
                strcpy(process_name, bp[i].process_name);
                for (int j = i; j < background_index - 1; j++)
                {
                    bp[j].pid = bp[j + 1].pid;
                    bp[j].job_num = bp[j + 1].job_num;
                    strcpy(bp[j].process_name, bp[j + 1].process_name);
                }
                background_index--;
                break;
            }

            else if (i == background_index - 1)
            {
                printf("ERROR: fg: no job with given job number exists\n");
                return;
            }
        }

        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        int r = tcsetpgrp(STDIN_FILENO, process_pid);
        if (r == -1)
        {
            perror("ERROR: fg: could not give job control of terminal");
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            return;
        }

        if (kill(process_pid, SIGCONT) != 0)
        {
            perror("ERROR: fg : unable to send continue signal to the process");
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            return;
        }

        forgnd_id = process_pid;
        strcpy(forgnd_name, token[0]);
        int status;
        waitpid(process_pid, &status, WUNTRACED);
        forgnd_id = -1;

        r = tcsetpgrp(STDIN_FILENO, getpgrp());
        if (r == -1)
        {
            perror("ERROR: fg: could not revert back terminal control of shell. Exiting the shell.\n");
            exit(1);
        }

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        if (WIFSTOPPED(status))
        {
            printf("fg: process is suspened.\n");
            bp[background_index].pid = process_pid;
            strcpy(bp[background_index].process_name, process_name);
            bp[background_index].job_num = job_index;
            job_index++;
            background_index++;
            qsort(bp, background_index, sizeof(bp[0]), string_comparator);
        }
    }
    else
    {
        printf("ERROR: fg: Number of arguments given is incorrect.\n");
    }

    return;
}