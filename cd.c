#include "headers.h"

void prev_update(char prev[], char *cur)
{
    int i = 0;

    while (cur[i] != '\0')
    {
        prev[i] = cur[i];
        i++;
    }
    prev[i] = '\0';
    ptr_to_prev = prev;
}

void command_cd(char *token[])
{
    pointer_to_curr = getcwd(current_directory, sizeof(current_directory));
    if (pointer_to_curr == NULL)
    {
        perror("Error: prompt (related to getcwd)");
    }
    
    int num_arguments = 0;
    for (int i = 0; token[i] != NULL; i++)
    {
        num_arguments++;
        if (num_arguments > 2)
        {
            break;
        }
    }

    if (num_arguments > 2)
    {
        printf("ERROR: cd : too many arguments\n");
    }

    else
    {
        if (num_arguments == 1)
        {
            int r;
            r = chdir(home_directory);
            if (r != 0)
            {
                perror("ERROR :cd");
            }

            else
            {
                prev_update(previous_directory, pointer_to_curr);
            }
        }
        else
        {
            char tilde[3];
            tilde[0] = '~';
            tilde[1] = '\0';

            char dash[3];
            dash[0] = '-';
            dash[1] = '\0';

            if (strcmp(token[1], tilde) == 0)
            {
                if (chdir(home_directory) != 0)
                {
                    perror("ERROR: cd");
                }
                else
                {
                    prev_update(previous_directory, pointer_to_curr);
                }
            }

            else if (strcmp(token[1], dash) == 0)
            {
                if (ptr_to_prev == NULL)
                {
                    printf("ERROR: cd: OLDPWD not set\n");
                    return;
                }
                else if (chdir(previous_directory) != 0)
                {
                    perror("ERROR: cd");
                }
                else
                {
                    printf("%s\n", previous_directory);
                    prev_update(previous_directory, pointer_to_curr);
                }
            }

            else if (token[1][0] == '~')
            {
                int r = chdir(home_directory);
                if (r != 0)
                {
                    perror("ERROR: cd");
                }
                token[1][0] = '.';
                if (r == 0)
                {
                    r = chdir(token[1]);
                    if (r != 0)
                    {
                        perror("Error: cd");
                        chdir(current_directory);
                    }
                    else
                    {
                        prev_update(previous_directory, pointer_to_curr);
                    }
                }
            }

            else
            {
                if (chdir(token[1]) != 0)
                {
                    perror("ERROR: cd");
                }
                else
                {
                    prev_update(previous_directory, pointer_to_curr);
                }
            }
        }
    }

    return;
}
