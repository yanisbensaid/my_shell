/*
** EPITECH PROJECT, 2023
** my_print_params
** File description:
** print params
*/

#include "../../include/my.h"

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        my_putstr(argv[i]);
        my_putchar('\n');
    }
    return 0;
}
