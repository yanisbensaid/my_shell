/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell2-matteo.chapelle-esmel
** File description:
** exec_pipe.c
*/

#include "../include/my.h"

static void add_token_to_array(char **arr, char *token, int *k)
{
    if (my_strlen(token) > 0) {
        arr[*k] = my_strdup(token);
        (*k)++;
    }
}

static void add_delimiter_to_array(char **arr, char delim, int *k)
{
    char delim_str[2] = {delim, '\0'};

    arr[*k] = my_strdup(delim_str);
    (*k)++;
}

char **str_to_arr2(const char *str, const char *delim)
{
    char **arr = malloc((my_strlen(str) * 2 + 1) * sizeof(char *));
    char *token = malloc(my_strlen(str) + 1);
    int j = 0;
    int k = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (my_strchr(delim, str[i]) != NULL) {
            token[j] = '\0';
            add_token_to_array(arr, token, &k);
            add_delimiter_to_array(arr, str[i], &k);
            j = 0;
        } else {
            token[j] = str[i];
            j++;
        }
    token[j] = '\0';
    add_token_to_array(arr, token, &k);
    arr[k] = NULL;
    free(token);
    return arr;
}

char *construct_command(char **arr, int start, int end)
{
    char *command = my_strdup("");

    for (int j = start; j < end; j++) {
        command = my_realloc(command,
            my_strlen(command) + my_strlen(arr[j]) + 2);
        my_strcat(command, arr[j]);
        if (j < end - 1)
            my_strcat(command, " ");
    }
    return command;
}

void create_pipe_node(binary_tree_t *tree, char **arr, int i)
{
    char *left_command = NULL;
    char *right_command = NULL;

    tree->type = PIPE;
    tree->left = create_node();
    tree->right = create_node();
    tree->data = my_strdup("|");
    left_command = construct_command(arr, 0, i);
    parse_command_line(left_command, tree->left);
    free(left_command);
    right_command = construct_command(arr, i + 1, arr_len(arr));
    parse_command_line(right_command, tree->right);
    free(right_command);
}

void create_sep_node(binary_tree_t *tree, char **arr, int i)
{
    char *left_command = NULL;
    char *right_command = NULL;

    tree->type = SEP;
    tree->left = create_node();
    tree->right = create_node();
    tree->data = my_strdup(";");
    left_command = construct_command(arr, 0, i);
    parse_command_line(left_command, tree->left);
    free(left_command);
    right_command = construct_command(arr, i + 1, arr_len(arr));
    parse_command_line(right_command, tree->right);
    free(right_command);
}

static void execute_left_subtree(binary_tree_t *tree, char **env, int *fd)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        status = exec_tree(tree->left, env);
        free_tree(tree);
        exit(status);
    }
}

static void execute_right_subtree(binary_tree_t *tree, char **env, int *fd)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        dup2(fd[0], 0);
        close(fd[1]);
        status = exec_tree(tree->right, env);
        free_tree(tree);
        exit(status);
    }
}

static void wait_for_child(int *fd, int *status)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(-1, status, WIFSTOPPED(0));
    waitpid(-1, status, WIFSTOPPED(0));
}

int execute_pipe_operation(binary_tree_t *tree, char **env)
{
    int fd[2];
    int status = 0;

    if (tree->left->data == NULL || tree->right->data == NULL ||
        tree->left->data[0] == '\0' || tree->right->data[0] == '\0') {
        my_putfd(2, "Invalid null command.\n");
        return 1;
    }
    pipe(fd);
    execute_left_subtree(tree, env, fd);
    execute_right_subtree(tree, env, fd);
    wait_for_child(fd, &status);
    return status;
}
