/*
** EPITECH PROJECT, 2023
** B-CPE-101-MPL-1-1-myprintf-matteo.chapelle-esmel
** File description:
** my_put_nbr_base
*/

#include <stdlib.h>
#include "../../include/my_printf.h"

int my_print_hexa(va_list ap)
{
    int cpt = 0;
    int nbr = va_arg(ap, int);

    if (nbr == 0) {
        cpt += my_putchar('0');
        return cpt;
    }
    cpt += my_putnbr_base(nbr, "0123456789abcdef");
    return cpt;
}

static int check(int len, int nb)
{
    int cpt = 0;

    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    cpt += my_putnbr_base(nb, "0123456789abcdef");
    return cpt;
}

static int check_neg(int len, int nb)
{
    int cpt = 0;

    cpt += my_putnbr_base(nb, "0123456789abcdef");
    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    return cpt;
}

static int put_format(int len, int nbr, int nb)
{
    int cpt = 0;

    if (nbr < 0) {
        len = (-nbr) - my_count_base(nb, "0123456789abcdef");
        cpt += check_neg(len, nb);
    } else {
        len = nbr - my_count_base(nb, "0123456789abcdef");
        cpt += check(len, nb);
    }
    return cpt;
}

static int check_first(char *c)
{
    int cpt = 0;

    if (c[0] == 35) {
        cpt += my_putstr("0x");
        return cpt;
    }
    return cpt;
}

int my_print_hexa_multi(va_list ap, char *c)
{
    int nb = va_arg(ap, int);
    int nbr;
    int len = 0;
    int cpt = 0;

    nbr = my_getnbr(c);
    if (nb == 0) {
        cpt += my_putchar('0');
        return cpt;
    }
    cpt += check_first(c);
    cpt += put_format(len, nbr, nb);
    return cpt;
}
