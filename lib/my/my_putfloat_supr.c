/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** my_putfloat_supr
*/

#include "../../include/my_printf.h"
#include <stdio.h>

static int verification(double v)
{
    int cpt = 0;
    int i = my_compute_power_rec(10, 5);
    int d = 10;

    while (v < i) {
        cpt += my_put_nbr(0);
        i = i / d;
    }
    return cpt;
}

static int supr_zero(double nb)
{
    int cpt = 0;
    int d = (int) nb;
    int temp = nb * 1000000 - d * 1000000 + 0.5;

    for (int i = 0; i < 7; i++) {
        if (temp % 10 == 0) {
            temp = temp / 10;
        }
    }
    cpt += my_put_nbr(temp);
    return cpt;
}

int my_putfloat_supr(double nb)
{
    int e = (int) nb;
    double v = nb - e;
    int cpt = 0;

    if (nb < 0) {
        nb = nb * -1;
        my_putchar(45);
        e = e * -1;
        v = v * -1;
    }
    cpt += my_put_nbr(e);
    my_putchar('.');
    cpt++;
    v = v * my_compute_power_rec(10, 6) + 0.5;
    cpt += verification(v);
    cpt += supr_zero(nb);
    return cpt;
}
