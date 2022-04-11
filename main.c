#include "headers.h"

void tokenize_input(char *input, char *token[])
{
    token[0] = strtok(input, ";");
    for (int i = 0; token[i] != NULL;)
    {
        i++;
        token[i] = strtok(NULL, ";");
    }
}

void shell_loop(void)
{
    while (1)
    {
        forgnd_id = -1;
        prompt();
        signal(SIGINT, ctrl_c);
        signal(SIGTSTP, ctrl_z);
        signal(SIGCHLD, finish_backgrd);
        char *input_string = NULL;
        ssize_t len = 0;
        ssize_t input_size = getline(&input_string, &len, stdin);
        if (input_size <= 0)
        {
            printf("\n");
            fflush(stdout);
            return;
        }
        char *token[1024];
        tokenize_input(input_string, token);

        for (int i = 0; token[i] != NULL; i++)
        {
            command(token[i]);
        }
        free(input_string);
    }
}

int main(int argc, char *argv[])
{
    shell_pid = getpid();

    if (gethostname(host_name, sizeof(host_name)) != 0)
    {
        perror("ERROR: gethostname ");
    }

    if (getlogin_r(user_name, sizeof(user_name)) != 0)
    {
        perror("ERROR: getlogin_r (user_name)");
    }

    ptr_to_home = getcwd(home_directory, sizeof(home_directory));
    if (ptr_to_home == NULL)
    {
        perror("ERROR (getcwd home_directory related)");
    }

    background_index = 0;
    job_index = 0;
    forgnd_id = -1;
    shell_loop();

    return 0;
}