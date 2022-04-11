#include "headers.h"

void path_to_dir(char *token, char *dir_path)
{
    if (token[0] == '~')
    {
        strcpy(dir_path, ptr_to_home);
        strcat(dir_path, token + 1);
    }
    else
    {
        strcpy(dir_path, token);
    }
    return;
}

int check_dir(char *dir_path)
{
    struct stat buffer;
    if (stat(dir_path, &buffer) == 0 && S_ISDIR(buffer.st_mode))
    {
        return 1;
    }

    else if (stat(dir_path, &buffer) == 0)
    {
        return 2;
    }

    char error[strlen(dir_path) + 25];
    strcpy(error, "ls: cannot access '");
    strcat(error, dir_path);
    strcat(error, "'");
    perror(error);
    return 0;
}

void ls_l_file(char *file_path)
{
    struct stat fs;
    if (stat(file_path, &fs) == 0 && S_ISDIR(fs.st_mode))
    {
        printf("d");
    }
    else
    {
        printf("-");
    }

    if (fs.st_mode & S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }

    if (fs.st_mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }

    if (fs.st_mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if (fs.st_mode & S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (fs.st_mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (fs.st_mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if (fs.st_mode & S_IROTH)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (fs.st_mode & S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (fs.st_mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    printf("\t");
    printf("%6ld\t", fs.st_nlink);
    printf("%s\t", getpwuid(fs.st_uid)->pw_name);
    printf("%s\t", getgrgid(fs.st_gid)->gr_name);
    printf("%12ld\t", fs.st_size);

    time_t now = time(NULL);
    struct tm time_file;
    struct tm time_now;
    localtime_r(&fs.st_mtime, &time_file);
    localtime_r(&now, &time_now);
    char string_month[][5] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    printf("%s %2d ", string_month[time_file.tm_mon], time_file.tm_mday);

    if (time_file.tm_year < time_now.tm_year)
    {
        time_now.tm_mon += 12;
    }

    if ((time_now.tm_mon - time_file.tm_mon) < 6)
    {
        printf("%02d:%02d  ", time_file.tm_hour, time_file.tm_min);
    }

    else if ((time_now.tm_mon - time_file.tm_mon) > 6)
    {
        printf("%4d  ", time_file.tm_year + 1900);
    }

    else if ((time_now.tm_mon - time_file.tm_mon) >= 0)
    {
        printf("%4d  ", time_file.tm_year + 1900);
    }
    else
    {
        printf("%02d:%02d  ", time_file.tm_hour, time_file.tm_min);
    }

    printf("%s\n", file_path);
}

void ls_dir(char *dir_path, int flag_a)
{
    struct dirent **names;
    int num_of_entries = scandir(dir_path, &names, NULL, alphasort);
    if (num_of_entries < 0)
    {
        perror("ERROR: ls");
    }
    else
    {
        for (int i = 0; i < num_of_entries; i++)
        {
            if (flag_a || names[i]->d_name[0] != '.')
            {
                printf("%s\n", names[i]->d_name);
            }
        }
    }
    return;
}

void ls_l_dir(char *dir_path, int flag_a)
{
    struct dirent **names;
    int num_of_entries = scandir(dir_path, &names, NULL, alphasort);
    if (num_of_entries < 0)
    {
        perror("ERROR: ls");
    }
    else
    {

        long long int total = 0;
        for (int i = 0; i < num_of_entries; i++)
        {
            if (flag_a || names[i]->d_name[0] != '.')
            {
                char *file_name = names[i]->d_name;
                char *file_path = (char *)malloc(sizeof(char) * (strlen(dir_path) + strlen(file_name) + 4));
                char *slash = "/";
                strcpy(file_path, dir_path);
                strcat(file_path, slash);
                strcat(file_path, file_name);
                struct stat fs;
                if (stat(file_path, &fs) == -1)
                {
                    perror("Error");
                }
                else
                {
                    total += fs.st_blocks;
                }
            }
        }
        printf("total %lld\n", total / 2);
        for (int i = 0; i < num_of_entries; i++)
        {
            if (flag_a || names[i]->d_name[0] != '.')
            {
                char *file_name = names[i]->d_name;
                char *file_path = (char *)malloc(sizeof(char) * (strlen(dir_path) + strlen(file_name) + 4));
                char *slash = "/";
                strcpy(file_path, dir_path);
                strcat(file_path, slash);
                strcat(file_path, file_name);

                struct stat fs;

                if (stat(file_path, &fs) == -1)
                {
                    perror("Error");
                }

                if (stat(file_path, &fs) == 0 && S_ISDIR(fs.st_mode))
                {
                    printf("d");
                }
                else
                {
                    printf("-");
                }

                if (fs.st_mode & S_IRUSR)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }

                if (fs.st_mode & S_IWUSR)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }

                if (fs.st_mode & S_IXUSR)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }

                if (fs.st_mode & S_IRGRP)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }
                if (fs.st_mode & S_IWGRP)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }
                if (fs.st_mode & S_IXGRP)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }
                if (fs.st_mode & S_IROTH)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }
                if (fs.st_mode & S_IWOTH)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }
                if (fs.st_mode & S_IXOTH)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }
                printf("\t");
                printf("%6ld\t", fs.st_nlink);
                printf("%s\t", getpwuid(fs.st_uid)->pw_name);
                printf("%s\t", getgrgid(fs.st_gid)->gr_name);
                printf("%12ld\t", fs.st_size);

                time_t now = time(NULL);
                struct tm time_file;
                struct tm time_now;
                localtime_r(&fs.st_mtime, &time_file);
                localtime_r(&now, &time_now);
                char string_month[][5] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

                printf("%s %2d ", string_month[time_file.tm_mon], time_file.tm_mday);

                if (time_file.tm_year < time_now.tm_year)
                {
                    time_now.tm_mon += 12;
                }

                if ((time_now.tm_mon - time_file.tm_mon) < 6)
                {
                    printf("%02d:%02d  ", time_file.tm_hour, time_file.tm_min);
                }

                else if ((time_now.tm_mon - time_file.tm_mon) > 6)
                {
                    printf("%4d  ", time_file.tm_year + 1900);
                }

                else if ((time_now.tm_mon - time_file.tm_mon) >= 0)
                {
                    printf("%4d  ", time_file.tm_year + 1900);
                }
                else
                {
                    printf("%02d:%02d  ", time_file.tm_hour, time_file.tm_min);
                }

                printf("%s\n", file_name);
                free(file_path);
            }
        }
    }
    return;
}

void command_ls(char *token[])
{
    int flag_a = 0;
    int flag_l = 0;
    int num_dir = 0;

    for (int i = 1; token[i] != NULL; i++)
    {
        if (token[i][0] == '-' && strlen(token[i]) > 1)
        {
            int k = 1;
            while (k < strlen(token[i]))
            {
                if (token[i][k] == 'a')
                {
                    flag_a = 1;
                }

                else if (token[i][k] == 'l')
                {
                    flag_l = 1;
                }

                else
                {
                    printf("ls: invalid option -- '%c'\n", token[i][k]);
                    return;
                }
                k++;
            }
        }

        else
        {
            num_dir++;
        }
    }

    char dir_path[1024];
    int check_path[num_dir + 1];
    int j = 0;

    if (num_dir == 0)
    {
        if (flag_l)
        {
            ls_l_dir(pointer_to_curr, flag_a);
        }
        else
        {
            ls_dir(pointer_to_curr, flag_a);
        }
    }

    for (int i = 1; token[i] != NULL; i++)
    {
        if (token[i][0] != '-' || strlen(token[i]) == 1)
        {
            path_to_dir(token[i], dir_path);
            check_path[j] = check_dir(dir_path);
            j++;
        }
    }

    j = 0;
    for (int i = 1; token[i] != NULL; i++)
    {
        if (token[i][0] != '-' || strlen(token[i]) == 1)
        {
            if (check_path[j] == 2)
            {
                path_to_dir(token[i], dir_path);
                if (flag_l)
                {
                    ls_l_file(dir_path);
                }
                else
                {
                    printf("%s\n", dir_path);
                }
            }

            j++;
        }
    }

    j = 0;
    for (int i = 1; token[i] != NULL; i++)
    {
        if (token[i][0] != '-' || strlen(token[i]) == 1)
        {
            if (check_path[j] == 1)
            {
                path_to_dir(token[i], dir_path);
                if (num_dir > 1)
                {
                    printf("%s:\n", dir_path);
                }
                if (flag_l)
                {
                    ls_l_dir(dir_path, flag_a);
                }
                else
                {
                    ls_dir(dir_path, flag_a);
                }
                printf("\n");
            }
            j++;
        }
    }
    return;
}