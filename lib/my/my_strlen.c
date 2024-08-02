/*
** EPITECH PROJECT, 2023
** day04
** File description:
** task03
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

int arr_len(char **array)
{
    int length = 0;

    while (array[length] != NULL) {
        length++;
    }
    return length;
}
