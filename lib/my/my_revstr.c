/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task03
*/

#include "../../include/my_printf.h"

char *my_revstr(char *str)
{
    int len = my_strlen(str);
    int nb = len / 2;
    int temp;

    for (int i = 0; i < nb; i++) {
        temp = str[len - 1];
        str[len - 1] = str[i];
        str[i] = temp;
        len--;
    }
    return str;
}
