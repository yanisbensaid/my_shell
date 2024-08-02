/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** aliases.c
*/

#include "../include/my.h"

alias_t *get_alias_list(alias_t *alias, int force)
{
    static alias_t *buff = NULL;

    if (force == 1)
        buff = alias;
    if (alias != NULL)
        buff = alias;
    return buff;
}

static char *get_alias(char *name, int avoid)
{
    alias_t *alias = get_alias_list(NULL, 0);
    int i = 0;

    while (alias != NULL) {
        if (i == avoid) {
            alias = alias->next;
            i++;
            continue;
        }
        if (my_strcmp(alias->alias, name) == 0)
            return alias->alias;
        alias = alias->next;
        i++;
    }
    return NULL;
}

static char *get_alias_cmd(char *name, int avoid)
{
    alias_t *alias = get_alias_list(NULL, 0);
    int i = 0;

    while (alias != NULL) {
        if (i == avoid) {
            alias = alias->next;
            i++;
            continue;
        }
        if (my_strcmp(alias->alias, name) == 0)
            return alias->command;
        alias = alias->next;
        i++;
    }
    return NULL;
}

static int get_alias_index(char *name)
{
    alias_t *alias = get_alias_list(NULL, 0);
    int i = 0;

    while (alias != NULL) {
        if (my_strcmp(alias->alias, name) == 0)
            return i;
        alias = alias->next;
        i++;
    }
    return -1;
}

static void replace_alias_in_input(char **input, int i, char *alias_cmd)
{
    char *temp = NULL;
    char **arr = NULL;
    char **arr2 = NULL;

    free(input[i]);
    input[i] = my_strdup(get_alias_cmd(alias_cmd, -1));
    arr = str_to_arr2(input[i], " ");
    free(input[i]);
    arr2 = arr;
    if (my_strcmp(arr[0], " ") == 0)
        arr2 = arr + 1;
    input[i] = check_alias(arr2);
    free_mem(arr);
    free(temp);
}

static void handle_alias_replacement(char **input, int i, char *alias_cmd,
    int *index)
{
    char *temp = my_strdup(input[i]);

    alias_cmd = get_alias(temp, *index);
    if (alias_cmd != NULL) {
        *index = get_alias_index(temp);
        replace_alias_in_input(input, i, alias_cmd);
    }
    if (alias_cmd == NULL)
        *index = -1;
    free(temp);
}

char *check_alias(char **input)
{
    static int index = -1;
    char *new_input = NULL;
    char *alias_cmd = NULL;
    bool should = true;

    for (int i = 0; input[i]; i++) {
        if (input[i][0] == '&' || input[i][0] == '|' || input[i][0] == ';' ||
            input[i][0] == '<' || input[i][0] == '>') {
            should = true;
            continue;
        }
        if (should == false || input[i][0] == ' ' || input[i][0] == '\t')
            continue;
        handle_alias_replacement(input, i, alias_cmd, &index);
        should = false;
    }
    new_input = construct_command(input, 0, arr_len(input));
    return new_input;
}

void free_aliases(void)
{
    alias_t *alias = get_alias_list(NULL, 0);
    alias_t *tmp = NULL;

    while (alias != NULL) {
        tmp = alias;
        alias = alias->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
    }
    get_alias_list(NULL, 1);
}

static void add_alias_parse(alias_t **alias, char *name, char *value)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    alias_t *current = *alias;

    clean_str(name, ' ');
    clean_str(name, '\t');
    clean_str(value, '\n');
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
}

alias_t *parse_aliases(void)
{
    alias_t *alias = NULL;
    char *token = NULL;
    char *line = NULL;
    size_t len = 0;
    FILE *fd = fopen(".42shrc", "r");

    if (fd == NULL)
        return NULL;
    while (getline(&line, &len, fd) != -1) {
        if (line[0] == '#' || line[0] == '\n')
            continue;
        if (my_strncmp(line, "alias", 5) == 0) {
            token = strtok(line + 5, "=");
            add_alias_parse(&alias, token, line + 5 + my_strlen(token) + 1);
        }
    }
    fclose(fd);
    free(line);
    return alias;
}
