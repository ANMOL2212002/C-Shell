#include "headers.h"

void command_replay(char *token[], int num)
{
    if (num < 6)
    {
        printf("ERROR: replay: too less arguments\n");
        return;
    }
    if (strcmp(token[num - 2], "-period") == 0 && strcmp(token[num - 4], "-interval") == 0 && strcmp(token[1], "-command") == 0)
    {
        if (check_num(token[num - 3]))
        {
            printf("ERROR: replay: given interval is not a valid number\n");
            return;
        }
        if (check_num(token[num - 1]))
        {
            printf("ERROR: replay: given interval is not a valid number\n");
            return;
        }
        int interval = atoi(token[num - 3]);
        int period = atoi(token[num - 1]);

        if (period == 0)
        {
            printf("ERROR: replay: given period is not positive\n");
            return;
        }
        if (interval == 0)
        {
            printf("ERROR: replay: given interval is not positive\n");
            return;
        }
        
        int n = period / interval;

        char input_str[1024] = " ";
        for (int i = 2; i < num - 4; i++)
        {
            strcat(input_str, token[i]);
            strcat(input_str, " ");
        }

        while (n--)
        {
            sleep(interval);
            char input[1024] = "";
            strcpy(input, input_str);
            command(input);
        }
    }
    else
    {
        printf("ERROR: replay: incorrect syntax of command\n");
    }
    return;
}