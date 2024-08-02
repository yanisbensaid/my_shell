/*
** EPITECH PROJECT, 2023
** my_pirntf
** File description:
** my_printadd
*/

#include "../../include/my_printf.h"
#include <stdio.h>

int my_putadd(unsigned long long nbr, char const *base)
{
    int cpt = 0;
    int index;
    int len = my_strlen(base);

    index = nbr % len;
    nbr = nbr / len;
    if (nbr > 0) {
        my_putadd(nbr, base);
    }
    cpt += my_putchar(base[index]);
    return cpt;
}

int my_printadd(unsigned long long nbr)
{
    int cpt = 0;

    cpt += my_putstr("0x");
    cpt += my_putadd(nbr, "0123456789abcdef");
    return cpt;
}

int my_printadd_va_list(va_list ap)
{
    int cpt = 0;

    cpt += my_printadd(va_arg(ap, unsigned long long));
    return cpt;
}
