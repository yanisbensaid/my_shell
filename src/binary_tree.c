/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell2-matteo.chapelle-esmel
** File description:
** binary_tree.c
*/

#include "../include/my.h"

static int handle_logical_operators(char **arr, binary_tree_t *tree, int i)
{
    if (arr_len(arr) > 1 && arr[i][0] == '&' && arr[i + 1] &&
        arr[i + 1][0] == '&') {
        create_and_node(tree, arr, i);
        return 1;
    }
    if (arr_len(arr) > 1 && arr[i][0] == '|' && arr[i + 1] &&
        arr[i + 1][0] == '|') {
        create_or_node(tree, arr, i);
        return 1;
    }
    if (arr[i][0] == '|') {
        create_pipe_node(tree, arr, i);
        return 1;
    }
    return 0;
}

static int handle_semicolon_and_redir(char **arr, binary_tree_t *tree, int i)
{
    if (arr[i][0] == ';') {
        create_sep_node(tree, arr, i);
        return 1;
    }
    if (arr_len(arr + i) > 1 && ((arr[i][0] == '<' && arr[i + 1][0] == '<') ||
        (arr[i][0] == '>' && arr[i + 1][0] == '>'))) {
        create_redir2_node(tree, arr, i, arr[i][0]);
        return 1;
    }
    if (arr[i][0] == '<' || arr[i][0] == '>') {
        create_redir_node(tree, arr, i, arr[i][0]);
        return 1;
    }
    return 0;
}

static int check_for_sep(char **arr, binary_tree_t *tree, int i)
{
    if (handle_logical_operators(arr, tree, i) == 1)
        return 1;
    if (handle_semicolon_and_redir(arr, tree, i) == 1)
        return 1;
    return 0;
}

binary_tree_t *create_node(void)
{
    binary_tree_t *node = malloc(sizeof(binary_tree_t));

    node->data = NULL;
    node->left = NULL;
    node->right = NULL;
    node->type = NONE;
    return node;
}

static void create_cmd_node(binary_tree_t *tree, char *command_line)
{
    tree->type = CMD;
    tree->data = my_strdup(command_line);
}

void parse_command_line(char *command_line, binary_tree_t *tree)
{
    char **arr = str_to_arr2(command_line, ";|><&");
    int i;

    for (i = 0; arr[i] != NULL; i++) {
        if (check_for_sep(arr, tree, i) == 1)
            break;
    }
    if (arr[i] == NULL)
        create_cmd_node(tree, command_line);
    free_mem(arr);
}

void free_tree(binary_tree_t *tree)
{
    if (tree->left != NULL)
        free_tree(tree->left);
    if (tree->right != NULL)
        free_tree(tree->right);
    free(tree->data);
    free(tree);
}

int b_tree(char *command_line, char **env)
{
    binary_tree_t *tree = create_node();
    int exit;

    parse_command_line(command_line, tree);
    exit = exec_tree(tree, env);
    free_tree(tree);
    return exit;
}
