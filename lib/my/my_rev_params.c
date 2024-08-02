/*
** EPITECH PROJECT, 2023
** my_rev_params
** File description:
** rev params
*/

#include "../../include/my.h"

int main(int argc, char **argv)
{
    for (int i = argc - 1; i > 0; i--) {
        my_putstr(argv[i]);
        my_putchar('\n');
    }
    return 0;
}
