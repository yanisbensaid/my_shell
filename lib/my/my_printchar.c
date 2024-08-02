/*
** EPITECH PROJECT, 2023
** my_putchar
** File description:
** print a char
*/

#include <stdarg.h>
#include <unistd.h>

int my_printchar(va_list ap)
{
    char c = va_arg(ap, int);

    write(1, &c, 1);
    return 1;
}
