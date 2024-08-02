/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** functions.c
*/

#include "../include/my.h"

int correct_path(char *bin, char **env, char **arr)
{
    char *right_path = find_executable(bin);
    int value;

    if (right_path != NULL) {
        value = exec_command(arr, right_path, env);
        free(right_path);
        return value;
    }
    if (my_strchr(bin, '/') == NULL) {
        my_putfd(2, bin);
        my_putfd(2, ": Command not found.\n");
        return 1;
    }
    return exec_command(arr, bin, env);
}

char *get_env_var(char *var)
{
    list_t **env = get_env(NULL);
    list_t *current = *env;

    while (current != NULL) {
        if (my_strncmp_env(current->data, var, my_strlen(var)) == 0) {
            return current->data + my_strlen(var) + 1;
        }
        current = current->next;
    }
    return NULL;
}

static int print_env_var_or_error(char **arr, int i)
{
    char *var = NULL;

    if (arr[i][0] == '$') {
        var = get_env_var(arr[i] + 1);
        if (var != NULL) {
            my_putfd(1, var);
            return 2;
        } else {
            my_putfd(2, arr[i] + 1);
            my_putfd(2, ": Undefined variable.\n");
            return 1;
        }
    }
    return 0;
}

int free_mem(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

int my_echo(char **arr)
{
    int exit;

    for (int i = 1; arr[i] != NULL; i++) {
        exit = print_env_var_or_error(arr, i);
        if (exit == 0)
            my_putfd(1, arr[i]);
        if (exit == 1)
            return 1;
        if (arr[i + 1] != NULL)
            my_putfd(1, " ");
    }
    my_putfd(1, "\n");
    return 0;
}
