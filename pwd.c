#include "headers.h"

void command_pwd()
{
    char curr_directory[1024];
    char *p = getcwd(curr_directory, sizeof(curr_directory));
    if (p == NULL)
    {
        perror("getcwd() error");
    }
    else
    {
        printf("%s\n",p);
    }
}