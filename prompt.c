#include "headers.h"

void prompt(void)
{
    pointer_to_curr = getcwd(current_directory, sizeof(current_directory));
    if (pointer_to_curr == NULL)
    {
        perror("Error: prompt (related to getcwd)");
    }

    else
    {
        int home_length = strlen(home_directory);
        char *ptr = current_directory;
        for (int i = 0; i < home_length; i++, ptr++)
        {
            if (home_directory[i] != current_directory[i])
            {
                printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m%s\x1B[0m>", user_name, host_name, current_directory);
                break;
            }

            else if (i == home_length - 1)
            {
                ptr++;
                printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~%s\x1B[0m>", user_name, host_name, ptr);
            }
        }
    }
}