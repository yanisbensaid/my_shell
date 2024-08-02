/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** env_functions.c
*/

#include "../include/my.h"

int exit_shell(void)
{
    int *run = get_bool();

    *run = 0;
    return 0;
}

int printenv(void)
{
    list_t **env = get_env(NULL);
    list_t *current = *env;

    while (current != NULL) {
        if (current->local == 0) {
            my_putfd(1, current->data);
            my_putfd(1, "\n");
        }
        current = current->next;
    }
    return 0;
}

void replace_value(list_t *target_node, char *value)
{
    if (target_node->type == 1) {
        free(target_node->data);
        target_node->data = value;
        return;
    }
    if (target_node->type == 0) {
        target_node->type = 1;
        target_node->data = value;
        return;
    }
}

static void proceed_setenv(list_t **env, char **arr)
{
    char *var = arr[1];
    char *value = arr[2] ? arr[2] : "\0";
    char *new_var = concat_strings(var, "=");
    char *new_var_value = concat_strings(new_var, value);
    list_t *current = *env;

    if (my_strcmp(var, "PATH") == 0)
        get_path_var(value);
    while (current != NULL) {
        if (my_strncmp(current->data, var, my_strlen(var)) == 0) {
            replace_value(current, new_var_value);
            free(new_var);
            return;
        }
        current = current->next;
    }
    append_node(env, new_var_value, 0);
    free(new_var);
}

int my_setenv(char **arr)
{
    list_t **env = get_env(NULL);

    if (arr_len(arr) > 3)
        return my_putfd(2, "setenv: Too many arguments.\n");
    if (arr_len(arr) == 1)
        return printenv();
    if (my_isalnum(arr[1][0]) == 0)
        return my_putfd(2, "setenv:"
            " Variable name must begin with a letter.\n");
    for (int i = 1; arr[1][i] != '\0'; i++) {
        if (my_isalnum(arr[1][i]) == 0)
            return my_putfd(2, "setenv: Variable name must contain "
                "alphanumeric characters.\n");
    }
    proceed_setenv(env, arr);
    return 0;
}

static list_t *find_var_node(list_t *env, char *var)
{
    list_t *current = env;

    while (current != NULL) {
        if (my_strncmp(current->data, var, my_strlen(var)) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static void shift_env_vars(list_t **env, list_t *node_to_remove)
{
    list_t *current = *env;

    if (current == node_to_remove) {
        *env = current->next;
    } else {
        while (current->next != node_to_remove) {
            current = current->next;
        }
        current->next = node_to_remove->next;
    }
    if (node_to_remove->type == 1)
        free(node_to_remove->data);
    free(node_to_remove);
}

int my_unsetenv(char **arr)
{
    list_t *node_to_remove;
    list_t **env = get_env(NULL);

    if (arr_len(arr) < 2) {
        my_putfd(2, "unsetenv: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; arr[i] != NULL; i++) {
        node_to_remove = find_var_node(*env, arr[i]);
        if (node_to_remove != NULL)
            shift_env_vars(env, node_to_remove);
    }
    return 0;
}
