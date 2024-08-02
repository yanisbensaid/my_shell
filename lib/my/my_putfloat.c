/*
** EPITECH PROJECT, 2023
** B-CPE-101-MPL-1-1-myprintf-matteo.chapelle-esmel
** File description:
** my_putfloat
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

int my_putfloat(double nb)
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
    v = v * my_compute_power_rec(10, 6) + 0.5;
    cpt += verification(v);
    if (v > 1) {
        cpt += my_put_nbr(v);
    }
    return 0;
}
