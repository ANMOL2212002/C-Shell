#include "headers.h"

void tokenize_pipe(char *input, char *token[])
{
    token[0] = strtok(input, "|");
    for (int i = 0; token[i] != NULL;)
    {
        i++;
        token[i] = strtok(NULL, "|");
    }
    return;
}

void command_pipeline(char *input)
{
    char *token[256];
    tokenize_pipe(input, token);

    int pipes = 0;
    int num_commands = 0;
    while (token[num_commands] != NULL)
    {
        num_commands++;
    }

    int file_des[2 * num_commands];
    for (int i = 0; i < 2 * (num_commands - 1); i += 2)
    {
        if (pipe(file_des + i) < 0)
        {
            perror("ERROR : pipelines: ");
            return;
        }
    }
    for (int i = 0; i < num_commands; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                dup2(file_des[2 * i + 1], STDOUT_FILENO);
            }
            else if (i == num_commands - 1)
            {
                dup2(file_des[2 * i - 2], STDIN_FILENO);
            }
            else
            {
                dup2(file_des[2 * i + 1], STDOUT_FILENO);
                dup2(file_des[2 * i - 2], STDIN_FILENO);
            }

            for (int j = 0; j < 2 * (num_commands - 1); j++)
            {
                close(file_des[j]);
            }

            command(token[i]);
            exit(2);
        }
    }

    for (int j = 0; j < 2 * (num_commands - 1); j++)
    {
        close(file_des[j]);
    }
    for (int i = 0; i < num_commands; i++)
    {
        wait(NULL);
    }
    return;
}

