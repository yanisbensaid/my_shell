/*
** EPITECH PROJECT, 2023
** B-PSU-100-MPL-1-1-myls-matteo.chapelle-esmel
** File description:
** concat_str.c
*/

#include "../include/my.h"

char *concat_strings(const char *str1, const char *str2)
{
    size_t len1 = my_strlen(str1);
    size_t len2 = my_strlen(str2);
    char *result = (char *)malloc(len1 + len2 + 1);

    for (size_t i = 0; i < len1; i++)
        result[i] = str1[i];
    for (size_t i = 0; i < len2; i++)
        result[len1 + i] = str2[i];
    result[len1 + len2] = '\0';
    return result;
}
