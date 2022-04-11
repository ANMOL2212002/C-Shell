#include "headers.h"

int string_comparator(const void *a, const void *b)
{
    struct backgrd_process *ip = (struct backgrd_process *)a;
    struct backgrd_process *iq = (struct backgrd_process *)b;
    if (strcmp(ip->process_name, iq->process_name) == 0)
    {
        return (ip->job_num - iq->job_num);
    }
    return strcmp(ip->process_name, iq->process_name);
}

void finish_backgrd(void)
{
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG || WUNTRACED)) > 0)
    {
        int stat = status;
        for (int i = 0; i < background_index; i++)
        {
            if (pid == bp[i].pid)
            {
                int exit_status = WIFEXITED(stat);
                if (exit_status == 1)
                {
                    printf("\nProcess %s with pid %d exited normally.\n", bp[i].process_name, pid);
                }
                else
                {
                    printf("\nProcess %s with pid %d exited abnormally.\n", bp[i].process_name, pid);
                }
                prompt();
                fflush(stdout);
                int exit_job = bp[i].job_num;
                /*
                for(int j = 0; j < background_index;j++)
                {
                    if(bp[j].job_num>exit_job)
                    {
                        bp[j].job_num--;
                    }
                }
                */
                for (int j = i; j < background_index - 1; j++)
                {
                    bp[j].pid = bp[j + 1].pid;
                    bp[j].job_num= bp[j+1].job_num;
                    strcpy(bp[j].process_name, bp[j + 1].process_name);
                }
                
                background_index--;
                break;
            }
        }
    }
}

void command_background(char *token[])
{
    pid_t ret_id = fork();

    if (ret_id < 0)
    {
        printf("ERROR: Forking child process failed\n");
    }
    else if (ret_id == 0)
    {
        setpgid(0, 0);
        int check;
        if (check == execvp(token[0], token) < 0)
        {
            printf("ERROR: execution of %s command failed\n", token[0]);
            exit(1);
        }
    }
    else
    {
        printf("%d\n", ret_id);
        bp[background_index].pid = ret_id;
        strcpy(bp[background_index].process_name, token[0]);
        bp[background_index].job_num = job_index;
        job_index++;
        background_index++;
        qsort(bp, background_index, sizeof(bp[0]), string_comparator);
    }
    return;
}
