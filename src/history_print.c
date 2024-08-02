/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** history_print.c
*/

#include "../include/my.h"

void print_history_entry(history_t *cur)
{
    char *temp = my_strdup(cur->time + 10);
    char *tok = strtok(temp, ":");
    char *tok2 = strtok(NULL, ":");

    my_put_nbr(cur->index);
    my_putstr("\t");
    my_putstr(tok);
    my_putstr(":");
    my_putstr(tok2);
    my_putstr("\t");
    my_putstr(cur->command);
    my_putstr("\n");
    free(temp);
}

history_t *reverse_history(history_t *head)
{
    history_t *prev = NULL;
    history_t *current = head;
    history_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

int print_history_borned(int nb, history_t *head)
{
    history_t *current = head;

    if (nb <= 0 || current == NULL)
        return 0;
    print_history_borned(nb - 1, current->next);
    print_history_entry(current);
    return 0;
}
