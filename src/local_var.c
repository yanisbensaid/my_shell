/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-matteo.chapelle-esmel
** File description:
** local_var
*/

#include "../include/my.h"

void remove_node(list_t **env, char *var)
{
    list_t *current = *env;
    list_t *tmp = NULL;

    for (; current->next != NULL; current = current->next) {
        if (my_strncmp_env(current->next->data, var, my_strlen(var)) == 0) {
            tmp = current->next->next;
            free(current->next->data);
            free(current->next);
            current->next = tmp;
            return;
        }
    }
}

int unset_local(char **arr)
{
    list_t **env = get_env(NULL);
    list_t *current = *env;

    for (; current != NULL; current = current->next) {
        if (my_strncmp_env(current->data, arr[1], my_strlen(arr[1])) == 0) {
            remove_node(env, arr[1]);
            return 0;
        }
    }
    return 0;
}

int no_value(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=')
            return 0;
    }
    return 1;
}

int my_setlocal(char **arr)
{
    list_t **env = get_env(NULL);
    list_t *current = *env;
    char *var = my_strdup(arr[1]);

    if (no_value(var) == 1)
        var = concat_strings(var, "=");
    for (; current != NULL; current = current->next) {
        if (my_strncmp_env(current->data, var, my_strlen(var)) == 0) {
            replace_value(current, var);
            return 0;
        }
    }
    append_node(env, var, 1);
    return 0;
}
