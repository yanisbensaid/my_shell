/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** env_linked_list.c
*/

#include "../include/my.h"

void free_list(void)
{
    list_t *tmp = NULL;
    list_t *head = *get_env(NULL);

    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (tmp->type == 1)
            free(tmp->data);
        free(tmp);
    }
    free(head);
}

list_t **get_env(char **env)
{
    static list_t *ll_env = {0};

    if (env != NULL)
        ll_env = parse_env_to_list(env);
    return &ll_env;
}

static list_t *new_node(char *data, int check)
{
    list_t *node = malloc(sizeof(list_t));

    if (node == NULL)
        return NULL;
    node->data = data;
    node->type = check;
    node->local = 0;
    node->next = NULL;
    return node;
}

void initialize_node(list_t **head, char *data)
{
    list_t *newNode = new_node(data, 0);
    list_t *current = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = newNode;
}

void append_node(list_t **head, char *data, int local)
{
    list_t *newNode = new_node(data, 1);
    list_t *current = NULL;

    newNode->local = local;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = newNode;
}

list_t *parse_env_to_list(char **env)
{
    list_t *head = NULL;

    for (int i = 0; env[i] != NULL; i++)
        initialize_node(&head, env[i]);
    return head;
}
