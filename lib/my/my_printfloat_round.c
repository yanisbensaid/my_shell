/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** my_printfloat_math
*/

#include <stdio.h>
#include "../../include/my_printf.h"

static int check(double nb)
{
    int c = 0;

    for (; nb < 1; c--) {
        nb *= 10;
    }
    for (; nb > 1; c++) {
        nb /= 10;
    }
    return c;
}

int my_printfloat_round(double nb)
{
    int cpt = 0;
    int c = 0;

    c += check(nb);
    if (c < -4) {
        cpt += my_printround_supr(nb);
        return cpt;
    }
    if (c >= 6) {
        cpt += my_printround_supr(nb);
        return cpt;
    }
    cpt += my_printdouble(nb);
    return cpt;
}

int my_printfloat_round_maj(double nb)
{
    int cpt = 0;
    int c = 0;

    c += check(nb);
    if (c < -4) {
        cpt += my_printround_supr_maj(nb);
        return cpt;
    }
    if (c >= 6) {
        cpt += my_printround_supr_maj(nb);
        return cpt;
    }
    cpt += my_printdouble(nb);
    return cpt;
}

int my_printfloat_round_va_list(va_list ap)
{
    int cpt = 0;

    cpt += my_printfloat_round(va_arg(ap, double));
    return cpt;
}

int my_printfloat_round_va_list_maj(va_list ap)
{
    int cpt = 0;

    cpt += my_printfloat_round_maj(va_arg(ap, double));
    return cpt;
}
