/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** signal_handler.c
*/

#include "../include/my.h"

void sigint_handler(int sig)
{
    int index;
    char *path = getcwd(NULL, 0);

    for (int i = 0; i < my_strlen(path); i++) {
        if (path[i] == '/')
            index = i;
    }
    (void)sig;
    my_putfd(1, "\033[2D");
    my_putfd(1, "\033[K");
    my_printf("\n"BOLD LBLUE"~%s ➜ "RESET, path + index);
    free(path);
}
