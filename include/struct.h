/*
** EPITECH PROJECT, 2023
** struct
** File description:
** struct
*/

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <SFML/Graphics.h>
#include "../include/my_printf.h"
#include "../include/my.h"

typedef struct ptr {
    char *c;
    int (*func)(va_list);
} ptr_fnc_t;

ptr_fnc_t array[] = {{"s", &my_printstr},
    {"i", &my_print_nbr},
    {"d", &my_print_nbr},
    {"c", &my_printchar},
    {"%", &my_printpourcent},
    {"f", &my_printfloat},
    {"x", &my_print_hexa},
    {"X", &my_print_hexa_maj},
    {"o", &my_print_octal},
    {"O", &my_print_octal},
    {"u", &my_print_uint},
    {"F", &my_printfloat},
    {"e", &my_print_round_va_list},
    {"E", &my_print_round_va_list_maj},
    {"g", &my_printfloat_round_va_list},
    {"G", &my_printfloat_round_va_list_maj},
    {"p", &my_printadd_va_list},
    {"lx", &my_put_luint_base_va_list},
    {0, NULL}};

typedef struct ptr2 {
    char *c;
    int (*func)(va_list, char *);
} ptr2_fnc_t;

ptr2_fnc_t array2[] = {{"d", &my_print_nbr_multi},
    {"x", &my_print_hexa_multi},
    {"X", &my_print_hexa_multi_maj},
    {"o", &my_print_octal_multi},
    {"c", &my_print_char_multi},
    {"s", &my_print_str_multi},
    {0, NULL}};
