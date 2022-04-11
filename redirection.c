#include "headers.h"

void command_redirection(char *token[])
{
    int flag_input = 0;
    int flag_output = 0;
    int index_output_file = -1;
    int index_input_file = -1;
    int flag_append = 0;

    char input[1024] = " ";
    for (int i = 0; strcmp(token[i], ">") != 0 && strcmp(token[i], "<") != 0 && strcmp(token[i], ">>") != 0; i++)
    {
        strcat(input, token[i]);
        strcat(input, " ");
    }

    for (int i = 0; token[i] != NULL; i++)
    {
        if (strcmp(token[i], "<") == 0)
        {
            flag_input = 1;
            while (token[i] != NULL && strcmp(token[i], ">") != 0 && strcmp(token[i], ">>") != 0)
            {
                index_input_file = i;
                i++;
            }
            if(token[i]==NULL)
            {
                break;
            }
        }

        if (strcmp(token[i], ">") == 0 && index_output_file == -1)
        {
            flag_output = 1;
            if (token[i + 1] != NULL)
            {
                index_output_file = i + 1;
            }
        }

        if (strcmp(token[i], ">>") == 0 && index_output_file == -1)
        {
            flag_output = 1;
            if (token[i + 1] != NULL)
            {
                flag_append = 1;
                index_output_file = i + 1;
            }
        }
    }

    //printf("%s\n", input);
    char input_file[1024];
    char output_file[1024];
    if (flag_input)
    {
        if (index_input_file == -1)
        {
            printf("ERROR: redirection: input file not provided\n");
            return;
        }
        strcpy(input_file, token[index_input_file]);
    }

    if (flag_output)
    {
        if (index_output_file == -1)
        {
            printf("ERROR: redirection: output file not provided\n");
            return;
        }
        strcpy(output_file, token[index_output_file]);
    }

    int prev_stdout = dup(STDOUT_FILENO);
    int prev_stdin = dup(STDIN_FILENO);
    int readfile;
    int writefile;
    if (flag_input)
    { 
        readfile = open(input_file, O_RDONLY);
        if (readfile < 0)
        {
            perror("ERROR: redirection : unable to open input file");
            close(prev_stdin);
            return;
        }
        int new_fd = 0;
        if (dup2(readfile, new_fd) == -1)
        {
            perror("ERROR : redirection:  unable to redirect input");
            return;
        }
    }

    if (flag_output)
    {
        int new_fd = STDOUT_FILENO;
        if (flag_append)
        {
            writefile = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (writefile < 0)
            {
                perror("ERROR: redirection : unable to open output file");
                close(prev_stdout);
                return;
            }
            if (dup2(writefile, new_fd) == -1)
            {
                perror("ERROR : redirection:  unable to open redirect output");
                return;
            }
        }

        else
        {
            writefile = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (writefile < 0)
            {
                perror("ERROR: redirection : unable to open output file");
                close(prev_stdout);
                return;
            }
            if (dup2(writefile, new_fd) == -1)
            {
                perror("ERROR : redirection:  unable to redirect output");
                return;
            }
        }
    }

    command(input);
    if (flag_input)
    {
        close(readfile);
        dup2(prev_stdin, 0);
    }
    if (flag_output)
    {
        close(writefile);
        dup2(prev_stdout, 1);
    }

    return;
}
