#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>


#define GREEN   "\x1B[32m"
#define BLUE   "\x1B[34m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

char host_name[HOST_NAME_MAX];
char user_name[LOGIN_NAME_MAX];
char home_directory[1024];
char previous_directory[1024];
char current_directory[1024];
char *pointer_to_curr;
char *ptr_to_home;
char *ptr_to_prev;
pid_t shell_pid;

int forgnd_id;
char forgnd_name[1024];

struct backgrd_process
{
    pid_t pid;
    int job_num;
    char process_name[64];
};
int background_index;
int job_index;
struct backgrd_process bp[1024];

int check_num(char *str);
int string_comparator(const void *a, const void *b);
int tokenize_command(char *input, char *token[]);
void tokenize_pipe(char *input, char *token[]);

void prompt(void);
void command(char *input);
void command_cd(char *token[]);
void command_echo(char *token[]);
void command_pwd();
void command_ls(char *token[]);
void command_foreground(char *token[]);
void command_background(char *token[]);
void command_pinfo(char *token[], int num);
void command_repeat(char *token[], int num);
void finish_backgrd();
void command_quit();
void command_jobs(char *token[], int num);
void command_sig(char *token[], int num);
void command_fg(char *token[], int num_tok);
void ctrl_c();
void ctrl_z();
void command_pipeline(char *input);
void command_redirection(char *token[]);
void command_replay(char *token[], int num);


#endif
