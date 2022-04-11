#include "headers.h"

int check_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < 48 || str[i] > 57)
        {
            return 1;
        }
    }
    return 0;
}

void command_sig(char *token[], int num)
{

    if (num == 3)
    {
        if (check_num(token[1]))
        {
            printf("ERROR: sig: given job number is not a valid number\n");
            return;
        }
        int job_number = atoi(token[1]);

        if (check_num(token[2]))
        {
            printf("ERROR: sig: given signal number is not a valid number\n");
            return;
        }
        int signal_number = atoi(token[2]);

        for (int i = 0; i < background_index; i++)
        {
            if (job_number - 1 == bp[i].job_num)
            {
                if (kill(bp[i].pid, signal_number)!=0)
                {
                    perror("ERROR: sig (kill)");
                }
                break;
            }
            else if (i == background_index - 1)
            {
                printf("ERROR: sig: no job with given job number exists\n");
            }
        }
    }
    else
    {
        printf("ERROR: sig: Number of arguments given is incorrect.\n");
    }

    return;
}