/*
** EPITECH PROJECT, 2023
** miniprintf
** File description:
** miniprintf
*/

#pragma once

#include <stdarg.h>

int my_putchar(char);

int my_putstr(char const *);

int my_put_nbr(int);

int sum_numbers(int, ...);

int sum_strings_length(int, ...);

void disp_stdarg(char *, ...);

int my_strlen(char const *);

char *my_strcpy(char *, char const *);

char *my_strcat(char *, char const *);

char *my_revstr(char *);

int my_compute_power_rec(int, int);

int my_printchar(va_list ap);

int my_print_nbr(va_list ap);

int my_printstr(va_list ap);

int my_printpourcent(va_list ap);

int my_printfloat(va_list ap);

int my_print_hexa(va_list ap);

int my_print_hexa_maj(va_list ap);

int my_print_octal(va_list ap);

int my_strlen(char const *);

int my_putnbr_base(int, char const *);

int my_printf(char *, ...);

int my_strcmp(char const *, char const *);

int my_print_uint(va_list ap);

unsigned int my_put_nbr_uint(unsigned int);

int my_print_nbr_multi(va_list ap, char *);

char *my_strncpy(char *, char const *, int);

int my_putfloat(double);

int my_print_round_va_list(va_list ap);

int my_print_round_va_list_maj(va_list ap);

int my_printround_maj(double);

int my_printround(double);

int my_putfloat_supr(double);

int my_printround_supr(double);

int my_printround_supr_maj(double);

int my_printfloat_round(double);

int my_printdouble(double);

int my_printfloat_round_va_list(va_list ap);

int my_printadd_va_list(va_list ap);

int my_printfloat_round_va_list_maj(va_list ap);

int my_getnbr(char const *);

char *int_tto_str(int, char *);

int my_print_hexa_multi(va_list ap, char *);

int my_print_hexa_multi_maj(va_list ap, char *);

int my_print_octal_multi(va_list ap, char *);

int my_count_base(int, char *);

long unsigned int my_put_nbr_luint(long unsigned int);

int my_put_luint_base_va_list(va_list ap);

int my_print_char_multi(va_list ap, char *);

int my_print_str_multi(va_list ap, char *);

int my_strncmp(char const *, char const *, int);
