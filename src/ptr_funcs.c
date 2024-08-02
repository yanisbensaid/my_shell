/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** ptrfnc.c
*/

#include "../include/my.h"
#include "../include/shell_structs.h"

char *clean_str(char *str, char c)
{
    char *p = str;

    while (*str != '\0') {
        if (*str != c) {
            *p = *str;
            p++;
        }
        str++;
    }
    *p = '\0';
    return str;
}

static void cleaned_str(char *str)
{
    clean_str(str, ' ');
    clean_str(str, '\t');
}

char *find_executable(char *command)
{
    char *path_var = my_strdup(get_env_var("PATH"));
    char *path = NULL;
    char *full_path = NULL;

    if (path_var == NULL)
        path_var = my_strdup(get_path_var(NULL));
    path = strtok(path_var, ":");
    while (path != NULL) {
        full_path = malloc(my_strlen(path) + my_strlen(command) + 2);
        my_strcpy(full_path, path);
        my_strcat(my_strcat(full_path, "/"), command);
        if (access(full_path, X_OK) == 0) {
            free(path_var);
            return full_path;
        }
        free(full_path);
        path = strtok(NULL, ":");
    }
    free(path_var);
    return NULL;
}

int check_ptr_funcs(char *path, char **env, char **arr)
{
    int ev = path[0] == '\0' ? 0 : -42;

    cleaned_str(path);
    if (ev == -42 && arr[0][0] == '!' && arr[0][1] != '\0')
        arr = point_dexclamation(arr);
    if (arr == NULL)
        return 0;
    arr = check_globbings(arr);
    for (int i = 0; ptr[i].s != NULL; i++) {
        if (ev == -42 && my_strcmp(arr[0], ptr[i].s) == 0 && ptr[i].f != NULL)
            ev = ptr[i].f(ptr[i].s, env, arr);
        if (ev == -42 && my_strcmp(arr[0], ptr[i].s) == 0 && ptr[i].f2 != NULL)
            ev = ptr[i].f2();
        if (ev == -42 && my_strcmp(arr[0], ptr[i].s) == 0 && ptr[i].f3 != NULL)
            ev = ptr[i].f3(arr);
    }
    if (ev == -42)
        ev = correct_path(arr[0], env, arr);
    free_mem(arr);
    return ev;
}

int *get_bool(void)
{
    static int run = 1;

    return &run;
}

char *get_path_var(char *str)
{
    static char *path_var = NULL;

    if (str != NULL)
        path_var = str;
    return path_var;
}
