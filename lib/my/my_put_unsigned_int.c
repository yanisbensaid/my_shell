/*
** EPITECH PROJECT, 2023
** u int
** File description:
** u int
*/
#include <limits.h>

#include "../../include/my_printf.h"

int my_put_uint(int nb)
{
    int cpt = 0;

    if (nb < 0) {
        cpt += my_put_nbr(UINT_MAX - (nb - 1));
    }
    if (nb > UINT_MAX){
        cpt += my_put_nbr(nb - 1);
    }
    cpt += my_put_nbr(nb);
    return cpt;
}
