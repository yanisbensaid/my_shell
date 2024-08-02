/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** alias_cmd.c
*/

#include "../include/my.h"

static int check_arguments(char **input)
{
    if (arr_len(input) == 1) {
        my_putfd(2, "alias: Too few arguments.\n");
        return 1;
    }
    return 0;
}

int re_alias(void)
{
    free_aliases();
    get_alias_list(parse_aliases(), 0);
    return 0;
}

static void proceed_unsetalias(alias_t **alias, alias_t *prev)
{
    alias_t *tmp = *alias;

    if (prev == NULL) {
        *alias = (*alias)->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
        get_alias_list(*alias, 1);
        return;
    }
    prev->next = (*alias)->next;
    free(tmp->alias);
    free(tmp->command);
    free(tmp);
}

int unalias(char **input)
{
    alias_t *alias = get_alias_list(NULL, 0);
    alias_t *prev = NULL;

    if (check_arguments(input) == 1)
        return 1;
    if (my_strcmp(input[1], "--all") == 0) {
        free_aliases();
        get_alias_list(NULL, 1);
        return 0;
    }
    while (alias != NULL) {
        if (my_strcmp(alias->alias, input[1]) == 0) {
            proceed_unsetalias(&alias, prev);
            return arr_len(input) >= 3 ? unalias(input + 1) : 0;
        }
        prev = alias;
        alias = alias->next;
    }
    my_putfd(2, "unalias: No such alias.\n");
    return 1;
}

int print_aliases(void)
{
    alias_t *alias = get_alias_list(NULL, 0);
    char *has_space = NULL;

    while (alias != NULL) {
        has_space = my_strchr(alias->command, ' ');
        my_putfd(1, alias->alias);
        my_putfd(1, "\t");
        if (has_space != NULL)
            my_putfd(1, "(");
        my_putfd(1, alias->command);
        if (has_space != NULL)
            my_putfd(1, ")");
        my_putfd(1, "\n");
        alias = alias->next;
    }
    return 0;
}

int check_if_alias_exists(char *alias, char **input)
{
    alias_t *alias_list = get_alias_list(NULL, 0);

    while (alias_list != NULL) {
        if (my_strcmp(alias_list->alias, alias) == 0) {
            alias_list->command = construct_command(input, 0, arr_len(input));
            return 1;
        }
        alias_list = alias_list->next;
    }
    return 0;
}

static void add_alias_cmd(alias_t **alias, char *name, char *value)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    alias_t *current = *alias;

    clean_str(name, ' ');
    clean_str(name, '\t');
    new_alias->alias = my_strdup(name);
    new_alias->command = my_strdup(value);
    new_alias->next = NULL;
    if (*alias == NULL) {
        *alias = new_alias;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_alias;
    get_alias_list(*alias, 1);
}

int alias(char **input)
{
    alias_t *alias = get_alias_list(NULL, 0);
    char *full_input = NULL;

    if (arr_len(input) == 1)
        return print_aliases();
    if (arr_len(input) == 2) {
        my_putfd(2, "alias: Too few arguments.\n");
        return 1;
    }
    if (arr_len(input) >= 3) {
        if (check_if_alias_exists(input[1], input + 2) == 1)
            return 0;
        full_input = construct_command(input, 2, arr_len(input));
        add_alias_cmd(&alias, input[1], full_input);
        free(full_input);
    }
    get_alias_list(alias, 1);
    return 0;
}
