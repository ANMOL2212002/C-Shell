#include "headers.h"

void command_bg(char *token[], int num_tok)
{
    if (num_tok == 2)
    {
        if (check_num(token[1]))
        {
            printf("ERROR: bg: given job number is not a valid number\n");
            return;
        }

        int bg_job_num = atoi(token[1]);

        for (int i = 0; i < background_index; i++)
        {
            if (bg_job_num - 1 == bp[i].job_num)
            {
                int bg_pid = bp[i].pid;
                if (kill(bg_pid, SIGCONT) != 0)
                {
                    perror("ERROR: bg (unable to send continue signal to the process)");
                }
                break;
            }

            else if (i == background_index - 1)
            {
                printf("ERROR: fg: no job with given job number exists\n");
            }
        }
    }
    else
    {
        printf("ERROR: bg: Number of arguments given is incorrect.\n");
    }
    return;
}