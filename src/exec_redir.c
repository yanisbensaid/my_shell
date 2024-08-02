/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell2-matteo.chapelle-esmel
** File description:
** exec_redir.c
*/

#include "../include/my.h"

void create_redir_node(binary_tree_t *tree, char **arr, int i, char sep)
{
    char *left_command = NULL;
    char *right_command = NULL;

    if (sep == '<')
        tree->type = L_REDIR;
    else
        tree->type = R_REDIR;
    tree->data = malloc(sizeof(char) * 2);
    tree->data[0] = sep;
    tree->data[1] = '\0';
    tree->left = create_node();
    tree->right = create_node();
    left_command = construct_command(arr, 0, i);
    parse_command_line(left_command, tree->left);
    free(left_command);
    right_command = construct_command(arr, i + 1, arr_len(arr));
    parse_command_line(right_command, tree->right);
    free(right_command);
}

void create_redir2_node(binary_tree_t *tree, char **arr, int i, char sep)
{
    char *left_command = NULL;
    char *right_command = NULL;

    if (sep == '<')
        tree->type = L_REDIR2;
    else
        tree->type = R_REDIR2;
    tree->data = malloc(sizeof(char) * 3);
    tree->data[0] = sep;
    tree->data[1] = sep;
    tree->data[2] = '\0';
    tree->left = create_node();
    tree->right = create_node();
    left_command = construct_command(arr, 0, i);
    parse_command_line(left_command, tree->left);
    free(left_command);
    right_command = construct_command(arr, i + 2, arr_len(arr));
    parse_command_line(right_command, tree->right);
    free(right_command);
}

static int r_redir_error(binary_tree_t *tree)
{
    if (tree->right->data == NULL || tree->right->data[0] == '\0') {
        my_putfd(2, "Missing name for redirect.\n");
        return 1;
    }
    if ((access(tree->right->data, X_OK) == 0 ||
        access(tree->right->data, R_OK) == -1) &&
        access(tree->right->data, F_OK) == 0) {
        my_putfd(2, tree->right->data);
        my_putfd(2, ": Permission denied.\n");
        return 1;
    }
    if (tree->left->data == NULL || tree->left->data[0] == '\0') {
        my_putfd(2, "Indalid null command.\n");
        return 1;
    }
    return 0;
}

static int handle_l_redir(binary_tree_t *tree, int *fd)
{
    if (tree->right->data == NULL || tree->right->data[0] == '\0') {
        my_putfd(2, "Missing name for redirect.\n");
        return 1;
    }
    if (tree->left->data == NULL || tree->left->data[0] == '\0') {
        my_putfd(2, "Indalid null command.\n");
        return 1;
    }
    if (access(tree->right->data, R_OK) == -1) {
        my_putfd(2, tree->right->data);
        my_putfd(2, ": No such file or directory.\n");
        return 1;
    }
    fd[0] = open(tree->right->data, O_RDONLY);
    if (fd[0] == -1)
        return 1;
    dup2(fd[0], 0);
    close(fd[0]);
    return 0;
}

static int handle_r_redirs(binary_tree_t *tree, int *fd)
{
    if (r_redir_error(tree) == 1)
        return 1;
    if (tree->type == R_REDIR)
        fd[1] = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd[1] = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd[1] == -1)
        return 1;
    dup2(fd[1], 1);
    close(fd[1]);
    return 0;
}

static int handle_l_redir2(int *fd, char *delimiter, char *path, int temp_fd)
{
    char *line = NULL;
    size_t len = 0;

    if (temp_fd == -1)
        return 1;
    my_putstr("? ");
    while ((getline(&line, &len, stdin)) != -1) {
        if (my_strncmp(line, delimiter, my_strlen(delimiter)) == 0)
            break;
        write(temp_fd, line, my_strlen(line));
        my_putstr("? ");
    }
    close(temp_fd);
    free(line);
    fd[0] = open(path, O_RDONLY);
    if (fd[0] == -1)
        return 1;
    dup2(fd[0], 0);
    close(fd[0]);
    return 0;
}

static int handle_redirection(binary_tree_t *tree, int *fd)
{
    int df;
    char *path = "/tmp/mysh_heredoc";

    clean_str(tree->right->data, ' ');
    clean_str(tree->right->data, '\t');
    if (tree->type == L_REDIR)
        return handle_l_redir(tree, fd);
    if (tree->type == R_REDIR || tree->type == R_REDIR2)
        return handle_r_redirs(tree, fd);
    if (tree->type == L_REDIR2) {
        df = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        return handle_l_redir2(fd, tree->right->data, path, df);
    }
    return 0;
}

static int execute_and_restore(binary_tree_t *tree, char **env,
    int save_stdout, int save_stdin)
{
    int status = exec_tree(tree->left, env);

    dup2(save_stdout, 1);
    dup2(save_stdin, 0);
    close(save_stdout);
    close(save_stdin);
    return status;
}

int execute_redirect_operation(binary_tree_t *tree, char **env)
{
    int fd[2];
    int status;
    int save_stdout = dup(1);
    int save_stdin = dup(0);

    status = handle_redirection(tree, fd);
    if (status == 1)
        return 1;
    return execute_and_restore(tree, env, save_stdout, save_stdin);
}
