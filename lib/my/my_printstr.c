/*
** EPITECH PROJECT, 2023
** day04
** File description:
** task02
*/

#include <stdarg.h>
#include "../../include/my_printf.h"

int my_printstr(va_list ap)
{
    int i = 0;
    char *str = va_arg(ap, char *);

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return my_strlen(str);
}
