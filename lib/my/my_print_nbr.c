/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** put_nbr
*/

#include <stdarg.h>
#include <limits.h>
#include "../../include/my_printf.h"
#include <stdlib.h>
#include <stdio.h>

int str_to_int(char *s)
{
    int num = 0;
    int n = my_strlen(s);

    for (int i = 0; i < n; i++) {
        num = num * 10 + (s[i] - 48);
    }
    return num;
}

char *int_tto_str(int nb, char *result)
{
    int temp = nb;
    int cpt = 0;

    while (temp > 0) {
        temp = temp / 10;
        cpt = cpt + 1;
    }
    for (int i = cpt - 1; i >= 0; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    return result;
}

int my_print_nbr(va_list ap)
{
    int nb = va_arg(ap, int);

    my_put_nbr(nb);
    return 0;
}

static int check(int len, int nb)
{
    int cpt = 0;

    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    cpt += my_put_nbr(nb);
    return cpt;
}

static int check_neg(int len, int nb)
{
    int cpt = 0;

    cpt += my_put_nbr(nb);
    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    return cpt;
}

static int put_format(int len, int nbr, int nb, char *res)
{
    int cpt = 0;

    if (nbr < 0) {
        len += (-nbr) - my_strlen(int_tto_str(nb, res));
        cpt += check_neg(len, nb);
    } else {
        len += nbr - my_strlen(int_tto_str(nb, res));
        cpt += check(len, nb);
    }
    return cpt;
}

static int check_first(char *c, int nbr)
{
    int cpt = 0;

    if (c[0] == 32) {
        my_putchar(' ');
        cpt ++;
        return cpt;
    }
    if (c[0] == 43 && nbr >= 0) {
        my_putchar(43);
        cpt ++;
        return cpt;
    }
    return cpt;
}

int my_print_nbr_multi(va_list ap, char *c)
{
    int nb = va_arg(ap, int);
    char *res = malloc(sizeof(char) * (my_strlen(c) + 1));
    int nbr;
    int len = 0;
    int cpt = 0;
    int count = 0;

    nbr = my_getnbr(c);
    count = cpt + check_first(c, nb);
    if (count == (cpt + 1)) {
        len = -1;
    }
    cpt += put_format(len, nbr, nb, res);
    return cpt;
}
