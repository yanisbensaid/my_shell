/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** exec_and.c
*/

#include "../include/my.h"

int exec_and(binary_tree_t *node, char **env)
{
    int status = 0;

    if (node->left != NULL)
        status = exec_tree(node->left, env);
    if (status == 0 && node->right != NULL)
        status = exec_tree(node->right, env);
    return status;
}

void create_and_node(binary_tree_t *tree, char **arr, int i)
{
    char *left_command = NULL;
    char *right_command = NULL;

    tree->type = AND;
    tree->left = create_node();
    tree->right = create_node();
    tree->data = my_strdup("&&");
    left_command = construct_command(arr, 0, i);
    parse_command_line(left_command, tree->left);
    free(left_command);
    right_command = construct_command(arr, i + 2, arr_len(arr));
    parse_command_line(right_command, tree->right);
    free(right_command);
}
