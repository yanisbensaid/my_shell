/*
** EPITECH PROJECT, 2023
** my_putchar
** File description:
** print a char
*/

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "../../include/my_printf.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

static int check(int len, char a)
{
    int cpt = 0;

    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    cpt += my_putchar(a);
    return cpt;
}

static int check_neg(int len, char a)
{
    int cpt = 0;

    cpt += my_putchar(a);
    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    return cpt;
}

static int put_format(int len, int nbr, char a)
{
    int cpt = 0;

    if (nbr < 0) {
        len = (-nbr) - 1;
        cpt += check_neg(len, a);
    } else {
        len = nbr - 1;
        cpt += check(len, a);
    }
    return cpt;
}

int my_print_char_multi(va_list ap, char *c)
{
    char a = va_arg(ap, int);
    int nbr;
    int len = 0;
    int cpt = 0;

    nbr = my_getnbr(c);
    cpt += put_format(len, nbr, a);
    return cpt;
}
