/*
** EPITECH PROJECT, 2023
** B-CPE-101-MPL-1-1-myprintf-matteo.chapelle-esmel
** File description:
** my_putfloat
*/

#include "../../include/my_printf.h"

#include <stdarg.h>

#include <stdio.h>

int verification(double v)
{
    int cpt = 0;

    if (v < 100000 && v >= 10000) {
        cpt += my_putstr("0");
    }
    if (v < 10000 && v >= 1000) {
        cpt += my_putstr("00");
    }
    if (v < 1000 && v >= 100) {
        cpt += my_putstr("000");
    }
    if (v < 100 && v >= 10) {
        cpt += my_putstr("0000");
    }
    if (v < 10 && v >= 1) {
        cpt += my_putstr("00000");
    }
    return cpt;
}

int my_printfloat(va_list ap)
{
    double nb = va_arg(ap, double);
    int e = (int) nb;
    double v = nb - e;
    int cpt = 0;

    if (nb < 0) {
        my_putchar(45);
        e = e * -1;
        v = v * -1;
    }
    cpt += my_put_nbr(e);
    my_putchar('.');
    cpt ++;
    v = v * my_compute_power_rec(10, 6) + 0.5;
    cpt += verification(v);
    cpt += my_put_nbr(v);
    return cpt;
}
