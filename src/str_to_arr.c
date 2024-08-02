/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** str_to_arr.c
*/

#include "my.h"

char *my_strsignal(int sig)
{
    switch (sig) {
        case SIGABRT:
            return "Aborted";
        case SIGFPE:
            return "Floating exception";
        case SIGILL:
            return "Illegal Instruction";
        case SIGINT:
            return "Interrupt";
        case SIGSEGV:
            return "Segmentation fault";
        case SIGTERM:
            return "Terminated";
        case SIGKILL:
            return "Killed";
        case SIGPIPE:
            return "Broken pipe";
        default:
            return "Unknown signal";
    }
}

char **str_to_arr(char *str, char *delim)
{
    char **result = NULL;
    int size = 0;
    char *tmp = my_strdup(str);
    char *token = strtok(tmp, delim);
    int i = 0;

    while (token != NULL) {
        size++;
        token = strtok(NULL, delim);
    }
    free(tmp);
    result = malloc((size + 1) * sizeof(char *));
    token = strtok(str, delim);
    while (token != NULL) {
        result[i] = my_strdup(token);
        i++;
        token = strtok(NULL, delim);
    }
    result[i] = NULL;
    return result;
}
