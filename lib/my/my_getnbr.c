/*
** EPITECH PROJECT, 2023
** getnbr
** File description:
** getnbr
*/

#include <limits.h>
#include "../../include/my_printf.h"

int is_alpha(char c)
{
    if (c > 64 && c < 91)
        return 1;
    else if (c > 96 && c < 123)
        return 1;
    else
        return 0;
}

int my_getnbr(char const *str)
{
    int n = 0;
    int start = 0;

    for (; str[start] != '\0' && is_alpha(str[start]) != 1; start++) {
        if (str[start] >= '0' && str[start] <= '9') {
            n = n * 10;
            n = n + str[start] - '0';
        }
    }
    if (n <= INT_MAX) {
        return (n);
    }
    return -1;
}
