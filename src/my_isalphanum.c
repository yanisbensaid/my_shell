/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-matteo.chapelle-esmel
** File description:
** my_isalphanum
*/

#include "../include/my.h"

int my_isalnum(int c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') || c == '_')
        return 1;
    else
        return 0;
}
