/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** put_nbr
*/

#include <limits.h>
#include "../../include/my_printf.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return 0;
    }
    if (nb < 0) {
        nb = nb * -1;
        my_putchar('-');
    }
    if (nb >= 10)
        my_put_nbr((nb / 10));
    my_putchar((nb % 10) + 48);
    return 0;
}
