/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** shell_structs.h
*/

#pragma once

typedef struct ptr4 {
    char *s;
    int (*f)(char *, char **, char **);
    int (*f2)(void);
    int (*f3)(char **);
} ptr4_fnc_t;

ptr4_fnc_t ptr[] = {
    {"cd", &my_cd, NULL, NULL},
    {"exit", NULL, &exit_shell, NULL},
    {"env", NULL, &printenv, NULL},
    {"/usr/bin/env", NULL, &printenv, NULL},
    {"echo", NULL, NULL, &my_echo},
    {"setenv", NULL, NULL, &my_setenv},
    {"unsetenv", NULL, NULL, &my_unsetenv},
    {"alias", NULL, NULL, &alias},
    {"unalias", NULL, NULL, &unalias},
    {"history", NULL, NULL, &print_history},
    {"realias", NULL, &re_alias, NULL},
    {"set", NULL, NULL, &my_setlocal},
    {"unset", NULL, NULL, &unset_local},
    {0, NULL, NULL, NULL}
};
