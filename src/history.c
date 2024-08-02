/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** history.c
*/

#include "../include/my.h"

void free_history(void)
{
    history_t *current = get_history(NULL);
    history_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->command);
        free(current->time);
        free(current);
        current = next;
    }
}

static int find_biggest_index(void)
{
    history_t *current = get_history(NULL);
    int biggest = 0;

    while (current != NULL) {
        if (current->index > biggest)
            biggest = current->index;
        current = current->next;
    }
    return biggest;
}

static history_t *create_history_node(char *command)
{
    history_t *new_node = malloc(sizeof(history_t));
    static int index = -1;
    time_t t = time(NULL);

    if (index == -1)
        index = find_biggest_index() + 1;
    new_node->command = my_strdup(command);
    new_node->time = my_strdup(asctime(localtime(&t)));
    clean_str(new_node->time, '\n');
    new_node->index = index;
    new_node->next = NULL;
    index++;
    return new_node;
}

void write_to_history(char *command, int fd)
{
    history_t *cur = get_history(NULL);
    history_t *new_node = create_history_node(command);
    char buff[11] = {0};
    time_t t = time(NULL);

    int_tto_str((int)t, buff);
    write(fd, buff, my_strlen(buff));
    write(fd, ";", 1);
    write(fd, command, my_strlen(command));
    write(fd, "\n", 1);
    if (cur == NULL) {
        get_history(new_node);
        return;
    }
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new_node;
}

int print_history(char **arr)
{
    history_t *cur = get_history(NULL);
    int nb = arr_len(arr) > 1 ? my_getnbr(arr[1]) : -1;

    nb = nb == 0 ? 1 : nb;
    if (nb != -1) {
        get_history(reverse_history(cur));
        print_history_borned(nb, get_history(NULL));
        get_history(reverse_history(get_history(NULL)));
        return 0;
    }
    while (cur != NULL) {
        print_history_entry(cur);
        cur = cur->next;
    }
    return 0;
}

static void add_to_history(char *line, history_t **history)
{
    history_t *cur = *history;
    history_t *new_node = malloc(sizeof(history_t));
    static int index = 1;
    char *time = strtok(line, ";");
    char *command = line + my_strlen(time) + 1;
    time_t timestamp = (time_t)my_getnbr(time);

    new_node->command = my_strdup(command);
    new_node->time = my_strdup(asctime(localtime(&timestamp)));
    clean_str(new_node->time, '\n');
    new_node->index = index;
    new_node->next = NULL;
    index++;
    if (cur == NULL) {
        *history = new_node;
        return;
    }
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new_node;
}

void parse_history(void)
{
    history_t *history = NULL;
    char *line = NULL;
    size_t len = 0;
    FILE *file = fopen(".42sh_history", "r");

    if (file == NULL)
        return;
    while (getline(&line, &len, file) != -1) {
        if (line[0] == '\n')
            continue;
        line[my_strlen(line) - 1] = '\0';
        add_to_history(line, &history);
    }
    fclose(file);
    free(line);
    get_history(history);
}

history_t *get_history(history_t *history)
{
    static history_t *save = NULL;

    if (history != NULL)
        save = history;
    return save;
}
