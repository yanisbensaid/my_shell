/*
** EPITECH PROJECT, 2023
** day04
** File description:
** task02
*/

#include "../../include/my_printf.h"
#include <stddef.h>
#include <unistd.h>

int my_putfd(int fd, char *str)
{
    if (str == NULL)
        return write(fd, "", 0);
    write(fd, str, my_strlen(str));
    return 42;
}

int my_putstr(char const *str)
{
    return write(1, str, my_strlen(str));
}

static int check(int len, char *a)
{
    int cpt = 0;

    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    cpt += my_putstr(a);
    return cpt;
}

static int check_neg(int len, char *a)
{
    int cpt = 0;

    cpt += my_putstr(a);
    for (int y = 0; y < len; y++) {
        my_putchar(' ');
        cpt ++;
    }
    return cpt;
}

static int put_format(int len, int nbr, char *a)
{
    int cpt = 0;

    if (nbr < 0) {
        len = (-nbr) - my_strlen(a);
        cpt += check_neg(len, a);
    } else {
        len = nbr - my_strlen(a);
        cpt += check(len, a);
    }
    return cpt;
}

int my_print_str_multi(va_list ap, char *c)
{
    char *a = va_arg(ap, char *);
    int nbr;
    int len = 0;
    int cpt = 0;

    nbr = my_getnbr(c);
    cpt += put_format(len, nbr, a);
    return cpt;
}
