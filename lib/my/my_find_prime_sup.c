/*
** EPITECH PROJECT, 2023
** day05
** File description:
** task07
*/

#include "../../include/my.h"

int my_find_prime_sup(int nb)
{
    while (my_is_prime(nb) != 1) {
        nb ++;
    }
    return nb;
}
