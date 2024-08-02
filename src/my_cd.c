/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell2-matteo.chapelle-esmel
** File description:
** my_cd.c
*/

#include "../include/my.h"

static int print_cd_error(char *path, int error)
{
    my_putfd(2, path);
    if (error == 3) {
        my_putfd(2, ": Permission denied.\n");
        return 1;
    }
    if (error == 2) {
        my_putfd(2, ": Not a directory.\n");
        return 1;
    }
    if (error == 1) {
        my_putfd(2, ": No such file or directory.\n");
        return 1;
    }
    if (error == 4) {
        my_putfd(2, ": Too many arguments.\n");
        return 1;
    }
    return 84;
}

static int check_file(char *path)
{
    struct stat sb;

    if (lstat(path, &sb) == -1)
        return 1;
    if (S_ISDIR(sb.st_mode) == 0)
        return 2;
    if (access(path, R_OK) == -1)
        return 3;
    return 0;
}

static int handle_home_directory(char *bin, char **env, int *i)
{
    my_cd(bin, env, (char *[]) {"cd", get_env_var("HOME"), NULL});
    *i = 1;
    return 2;
}

static int handle_previous_directory(char *bin, char **env, int *i)
{
    if (*i == 0) {
        my_putfd(2, ": No such file or directory.\n");
        return 1;
    }
    my_cd(bin, env, (char *[]) {"cd", get_env_var("OLDPWD"), NULL});
    return 2;
}

static int handle_dir_with_home(char **arr, char *bin, char **env, int *i)
{
    char *path_with_home = concat_strings(get_env_var("HOME"), arr[1] + 1);

    my_cd(bin, env, (char *[]) {"cd", path_with_home, NULL});
    free(path_with_home);
    *i = 1;
    return 2;
}

static int handle_directory_change(char **arr, char *bin, char **env, int *i)
{
    if (arr_len(arr) == 1 || my_strcmp(arr[1], "~") == 0)
        return handle_home_directory(bin, env, i);
    if (my_strcmp(arr[1], "-") == 0)
        return handle_previous_directory(bin, env, i);
    if (arr[1][0] == '~' && arr[1][1] == '/')
        return handle_dir_with_home(arr, bin, env, i);
    return 0;
}

static int check_arguments(char **arr, char *bin, char **env, int *i)
{
    if (arr_len(arr) > 2)
        return print_cd_error("cd", 4);
    return handle_directory_change(arr, bin, env, i);
}

static int handle_cd_errors(char *path, int *i)
{
    int error = check_file(path);

    if (error != 0)
        return print_cd_error(path, error);
    if (chdir(path) == -1)
        return print_cd_error(path, 3);
    *i = 1;
    return 0;
}

int change_directory(char *path, char *actual_pwd)
{
    my_setenv((char *[]){"setenv", "OLDPWD", actual_pwd, NULL});
    return my_setenv((char *[]){"setenv", "PWD", getcwd(path, 1000), NULL});
}

int my_cd(char *bin, char **env, char **arr)
{
    static int i = 0;
    char buff[1000] = {0};
    char *actual_pwd = get_env_var("PWD");
    int check_args_result;
    int handle_errors_result;

    check_args_result = check_arguments(arr, bin, env, &i);
    if (check_args_result != 0) {
        if (check_args_result == 2)
            return 0;
        return check_args_result;
    }
    handle_errors_result = handle_cd_errors(arr[1], &i);
    if (handle_errors_result != 0)
        return handle_errors_result;
    return change_directory(buff, actual_pwd);
}
