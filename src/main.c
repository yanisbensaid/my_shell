/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** main.c
*/

#include "../include/my.h"

static int handle_exec_errors(char *path)
{
    struct stat sb;

    if (lstat(path, &sb) == -1) {
        my_putfd(2, path);
        my_putfd(2, ": Command not found.\n");
        return 1;
    }
    if (S_ISDIR(sb.st_mode) == 1) {
        my_putfd(2, path);
        my_putfd(2, ": Permission denied.\n");
        return 1;
    }
    return 0;
}

static int parent_process(int pid)
{
    int status;
    char *error = NULL;

    waitpid(pid, &status, WIFSTOPPED(0));
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        my_putfd(2, my_strsignal(WTERMSIG(status)));
        error = WCOREDUMP(status) ? " (core dumped)\n" : "\n";
        my_putfd(2, error);
        return 128 + WTERMSIG(status);
    }
    return 1;
}

static int child_process(char *path, char **arr, char **env)
{
    if (execve(path, arr, env) == -1) {
        if (errno == ENOEXEC) {
            my_putfd(2, path);
            my_putfd(2, ": Exec format error. Wrong Architecture.\n");
        }
        exit_shell();
        return 1;
    }
    free(path);
    free_mem(arr);
    return 0;
}

int parse(char *line, char **env, int fd)
{
    int exit;
    char **arr = NULL;

    clean_str(line, '\n');
    write_to_history(line, fd);
    arr = str_to_arr2(line, " \t;><|&");
    line = check_alias(arr);
    free_mem(arr);
    arr = str_to_arr(line, ";");
    for (int i = 0; arr[i] != NULL; i++)
        exit = b_tree(arr[i], env);
    if (exit == 84)
        exit = 1;
    free_mem(arr);
    free(line);
    return exit;
}

static char *prepare_command(char **arr, char *path)
{
    if (arr[0][0] == '~' && arr[0][1] == '/') {
        path = concat_strings(get_env_var("HOME"), arr[0] + 1);
        free(arr[0]);
        arr[0] = path;
    }
    if (handle_exec_errors(path) == 1)
        return NULL;
    return path;
}

int exec_command(char **arr, char *path, char **env)
{
    int new_pid;

    path = prepare_command(arr, path);
    if (path == NULL)
        return 1;
    new_pid = fork();
    if (new_pid > 0) {
        return parent_process(new_pid);
    }
    if (new_pid == 0) {
        return child_process(path, arr, env);
    }
    return 0;
}

static int not_a_tty(char **env, int fd)
{
    char *line = NULL;
    size_t len = 0;
    int exit = 0;

    while (getline(&line, &len, stdin) != -1) {
        if (my_strlen(line) > 1)
            exit = parse(line, env, fd);
        if (exit == 42)
            return 1;
    }
    free_list();
    free(line);
    close(fd);
    free_aliases();
    free_history();
    return exit;
}

static char *get_prompt(void)
{
    char *path = get_env_var("PWD");
    int index = 0;

    if (path == NULL)
        return "";
    for (int i = 0; path[i] != '\0'; i++)
        if (path[i] == '/')
            index = i;
    return path + index;
}

static int is_a_tty(char **env, int fd)
{
    char *line = NULL;
    size_t len = 0;
    int *run = get_bool();

    signal(SIGINT, &sigint_handler);
    while (*run == 1) {
        my_printf(BOLD LBLUE"~%s ➜ "RESET, get_prompt());
        if (getline(&line, &len, stdin) == -1)
            exit_shell();
        if (my_strlen(line) > 1)
            parse(line, env, fd);
    }
    free(line);
    free_list();
    close(fd);
    free_aliases();
    free_history();
    return 0;
}

int main(int ac, char **av, char **env)
{
    int fd;

    (void)av;
    if (ac != 1)
        return 84;
    fd = open(".42sh_history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    get_env(env);
    get_path_var(get_env_var("PATH"));
    get_alias_list(parse_aliases(), 1);
    parse_history();
    if (isatty(0) == 0)
        return not_a_tty(env, fd);
    return is_a_tty(env, fd);
}
