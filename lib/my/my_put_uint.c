/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** put_nbr
*/

#include "../../include/my_printf.h"

static void int_ttoo_str(unsigned int nb, char *result)
{
    unsigned int temp = nb;
    int cpt = 0;

    while (temp > 0) {
        temp = temp / 10;
        cpt = cpt + 1;
    }
    for (int i = cpt - 1; i >= 0; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    my_putstr(result);
}

unsigned int my_put_nbr_uint(unsigned int nb)
{
    char result[100] = {0};

    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    int_ttoo_str(nb, result);
    return my_strlen(result);
}

static void int_to_str(unsigned int nb, char *result)
{
    long unsigned int temp = nb;
    int cpt = 0;

    while (temp > 0) {
        temp = temp / 10;
        cpt = cpt + 1;
    }
    for (int i = cpt - 1; i >= 0; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    my_putstr(result);
}

long unsigned int my_put_nbr_luint(long unsigned int nb)
{
    char result[100] = {0};

    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    int_to_str(nb, result);
    return my_strlen(result);
}
