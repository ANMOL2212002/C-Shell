#include "headers.h"

void command_foreground(char *token[])
{
    pid_t ret_id = fork();
    if (ret_id < 0)
    {
        printf("ERROR: Forking child process failed\n");
    }
    else if (ret_id == 0)
    {
    setpgid(0, 0);
        int check = execvp(token[0], token);
        if (check < 0)
        {
            printf("ERROR: execution of %s command failed\n", token[0]);
            exit(1);
        }
    }
    else
    {
        int status = 0;
       /* printf("%d\n", ret_id);
        char *mas[2];
        mas[0] = "pinfo ";
        char m[10];
        sprintf(m, "%d", ret_id);
        int i = 0;
        while (m[i] != '\0')
        {
            mas[1][i] = m[i];
            i++;
        }
        mas[1][i] = '\0';
        command_pinfo(mas, 2);*/
        forgnd_id = ret_id;
        strcpy(forgnd_name,token[0]);
        waitpid(ret_id, &status, WUNTRACED);
        forgnd_id = -1;
    }
    return;
}
