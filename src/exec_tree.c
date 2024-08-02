/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** exec_tree.c
*/

#include "../include/my.h"

int exec_cmd_and_sep(binary_tree_t *tree, char **env)
{
    int status = 0;

    if (tree->type == CMD) {
        if (tree->data == NULL || tree->data[0] == '\0')
            return status;
        status = check_ptr_funcs(tree->data, env,
            str_to_arr(tree->data, " \t\n"));
    }
    if (tree->type == SEP) {
        if (tree->left != NULL)
            status = exec_tree(tree->left, env);
        if (tree->right != NULL)
            status = exec_tree(tree->right, env);
    }
    return status;
}

int exec_redir_and_logical(binary_tree_t *tree, char **env)
{
    int status = 0;

    if (tree->type == PIPE)
        status = execute_pipe_operation(tree, env);
    if (tree->type == L_REDIR || tree->type == R_REDIR ||
        tree->type == L_REDIR2 || tree->type == R_REDIR2)
        status = execute_redirect_operation(tree, env);
    if (tree->type == AND)
        status = exec_and(tree, env);
    if (tree->type == OR)
        status = exec_or(tree, env);
    return status;
}

int exec_tree(binary_tree_t *tree, char **env)
{
    int status = 0;

    status = exec_cmd_and_sep(tree, env);
    if (status == 0)
        status = exec_redir_and_logical(tree, env);
    return status;
}
