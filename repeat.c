#include "headers.h"

void check_num_repeat(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < 48 || str[i] > 57)
        {
            printf("Error: The first argument to repeat command must be a number\n");
            return;
        }
    }
    return;
}

void command_repeat(char *token[], int num)
{
    if (num < 2)
    {
        printf("ERROR: repeat: too less arguments\n");
        return;
    }

    check_num_repeat(token[1]);
    int n = atoi(token[1]);
    while (n--)
    {
        int i = 2;
        char input[1024] = " ";
        while (token[i] != NULL)
        {
            strcat(input, token[i]);
            strcat(input, " ");
            i++;
        }
        command(input);
    }
    return;
}