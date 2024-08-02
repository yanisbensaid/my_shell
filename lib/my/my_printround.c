/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** my_printround
*/

#include "../../include/my_printf.h"
#include <stdio.h>

static int divs(double nb)
{
    int c = 0;
    int d = 10;

    while (nb > 10) {
        nb = nb / d;
        c++;
    }
    return c;
}

static int mutl(double nb)
{
    int c = 0;

    while (nb < 1) {
        nb = nb * 10;
        c++;
    }
    return c;
}

static int negative(double nb)
{
    if (nb < 0) {
        nb = nb * -1;
        my_putchar('-');
    }
    return 1;
}

static int my_putzero(int c)
{
    if (c < 10) {
        my_putchar('0');
    }
    return 1;
}

static int part_one(double nb, int c)
{
    int cpt = 0;

    nb = nb / my_compute_power_rec(10, c);
    cpt += my_putfloat(nb);
    cpt += my_putstr("e+");
    cpt += my_putzero(c);
    cpt += my_put_nbr(c);
    return cpt;
}

static int part_one_maj(double nb, int c)
{
    int cpt = 0;

    nb = nb / my_compute_power_rec(10, c);
    cpt += my_putfloat(nb);
    cpt += my_putstr("E+");
    cpt += my_putzero(c);
    cpt += my_put_nbr(c);
    return cpt;
}

int my_printround(double nb)
{
    int c = 0;
    int cpt = 0;

    negative(nb);
    if (nb > 1) {
        c += divs(nb);
        cpt += part_one(nb, c);
    }
    if (nb <= 1) {
        c += mutl(nb);
        nb = nb * my_compute_power_rec(10, c);
        cpt += my_putfloat(nb);
        cpt += my_putstr("e-");
        cpt += my_putzero(c);
        cpt += my_put_nbr(c);
    }
    return cpt;
}

int my_printround_maj(double nb)
{
    int c = 0;
    int cpt = 0;

    negative(nb);
    if (nb >= 1) {
        c += divs(nb);
        cpt += part_one_maj(nb, c);
    }
    if (nb < 1) {
        c += mutl(nb);
        nb = nb * my_compute_power_rec(10, c);
        cpt += my_putfloat(nb);
        cpt += my_putstr("E-");
        cpt += my_putzero(c);
        cpt += my_put_nbr(c);
    }
    return cpt;
}

int my_print_round_va_list(va_list ap)
{
    int cpt = 0;
    double nb = va_arg(ap, double);

    cpt += my_printround(nb);
    return cpt;
}

int my_print_round_va_list_maj(va_list ap)
{
    int cpt = 0;
    double nb = va_arg(ap, double);

    cpt += my_printround_maj(nb);
    return cpt;
}
