/*
** EPITECH PROJECT, 2023
** u int
** File description:
** u int
*/
#include <limits.h>

#include "../../include/my_printf.h"

int my_print_uint(va_list ap)
{
    int nb = va_arg(ap, int);
    unsigned int result = nb;
    int cpt = 0;

    if (nb < 0) {
        result = UINT_MAX + nb + 1;
    }
    cpt += my_put_nbr_uint(result);
    return cpt;
}
