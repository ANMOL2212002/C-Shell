#include "headers.h"

void command_echo(char *token[])
{
    for(int i = 1;token[i]!=NULL;i++)
    {
        printf("%s ",token[i]);
    }
    printf("\n");
}