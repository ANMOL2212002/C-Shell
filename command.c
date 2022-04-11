#include "headers.h"

int tokenize_command(char *input, char *token[])
{
    token[0] = strtok(input, " \r\t\n");
    int i = 0;
    for (; token[i] != NULL;)
    {
        i++;
        token[i] = strtok(NULL, " \r\t\n");
    }
    return i;
}

int pipelines_present(char *token[])
{
    int i = 0;
    while (token[i] != NULL)
    {
        if (strcmp(token[i], "|") == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int redirection_present(char *token[])
{
    int i = 0;
    while (token[i] != NULL)
    {
        if (strcmp(token[i], ">") == 0 || strcmp(token[i], "<") == 0 || strcmp(token[i], ">>") == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void command(char *input)
{
    char *token[1024];
    char input2[1024];
    strcpy(input2, input);
    int num_tok = tokenize_command(input, token);
    if (num_tok == 0)
    {
        ;
    }
    else if (pipelines_present(token))
    {

        command_pipeline(input2);
    }
    else if (redirection_present(token))
    {
        command_redirection(token);
    }
    else if (strcmp(token[0], "cd") == 0)
    {
        command_cd(token);
    }
    else if (strcmp(token[0], "echo") == 0)
    {
        command_echo(token);
    }
    else if (strcmp(token[0], "pwd") == 0)
    {
        command_pwd();
    }
    else if (strcmp(token[0], "ls") == 0)
    {
        command_ls(token);
    }
    else if (strcmp(token[num_tok - 1], "&") == 0)
    {
        token[num_tok - 1] = NULL;
        command_background(token);
    }
    else if (token[num_tok - 1][strlen(token[num_tok - 1]) - 1] == '&')
    {
        token[num_tok - 1][strlen(token[num_tok - 1]) - 1] = '\0';
        command_background(token);
    }
    else if (strcmp(token[0], "pinfo") == 0)
    {
        command_pinfo(token, num_tok);
    }
    else if (strcmp(token[0], "repeat") == 0)
    {
        command_repeat(token, num_tok);
    }
    else if (strcmp(token[0], "jobs") == 0)
    {
        command_jobs(token, num_tok);
    }
    else if (strcmp(token[0], "sig") == 0)
    {
        command_sig(token, num_tok);
    }
    else if (strcmp(token[0], "fg") == 0)
    {
        command_fg(token, num_tok);
    }
    else if (strcmp(token[0], "replay") == 0)
    {
        command_replay(token, num_tok);
    }
    else if (strcmp(token[0], "quit") == 0)
    {
        command_quit(token[0]);
    }
    else
    {
        command_foreground(token);
    }

    return;
}