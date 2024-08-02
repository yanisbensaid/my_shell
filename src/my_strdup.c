/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell1-matteo.chapelle-esmel
** File description:
** my_strdup.c
*/

#include "../include/my.h"

char **my_arrdup(char **arr)
{
    char **new_arr = NULL;
    int len = arr_len(arr);

    new_arr = malloc((len + 1) * sizeof(char *));
    if (new_arr == NULL)
        return NULL;
    for (int i = 0; i < len; i++)
        new_arr[i] = my_strdup(arr[i]);
    new_arr[len] = NULL;
    return new_arr;
}

char *my_strchr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == c)
            return (char *)str;
        str++;
    }
    if (c == '\0')
        return (char *)str;
    return NULL;
}

char *my_strndup(const char *src, size_t n)
{
    char *str = NULL;
    size_t len = my_strlen(src);

    if (src == NULL)
        return NULL;
    if (n > len)
        n = len;
    str = malloc((n + 1) * sizeof(char));
    if (str == NULL)
        return NULL;
    my_strncpy(str, src, n);
    str[n] = '\0';
    return str;
}

char *my_strdup(const char *src)
{
    char *str = NULL;
    size_t len;

    if (src == NULL)
        return NULL;
    len = my_strlen(src);
    str = malloc((len + 1) * sizeof(char));
    if (str == NULL)
        return NULL;
    my_strcpy(str, src);
    return str;
}
