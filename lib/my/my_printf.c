/*
** EPITECH PROJECT, 2023
** B-CPE-101-MPL-1-1-miniprintf-matteo.chapelle-esmel
** File description:
** my_printf
*/

#include <stdarg.h>

#include <stdlib.h>

#include <stdio.h>

#include <stddef.h>

#include "../../include/my_printf.h"

#include "../../include/struct.h"

int my_put_arg(va_list ap, char *flag)
{
    for (int i = 0; array2[i].c != 0; i++) {
        if ((my_strlen(flag) - 1) > 0 &&
        flag[my_strlen(flag) - 1] == array2[i].c[0]) {
            return array2[i].func(ap, flag);
        }
    }
    for (int i = 0; array[i].func; i++) {
        if (flag[0] == array[i].c[0]) {
            return array[i].func(ap);
        }
    }
    my_putchar('%');
    my_putstr(flag);
    return my_strlen(flag) + 1;
}

char *check_array(char c, int *res, char *flag)
{
    for (int y = 0; array[y].func; y++) {
        if (c == array[y].c[0]) {
            flag[my_strlen(flag)] = array[y].c[0];
            *res = 1;
        }
    }
    return flag;
}

char *multi_flag(char *s, char *flag, int *i)
{
    int k = 0;
    int res = 0;

    flag = check_array(s[*i], &res, flag);
    for (int y = 0; array[y].func; y++) {
        while (res == 0) {
            flag[k] = s[*i];
            *i = *i + 1;
            k++;
            flag = check_array(s[*i], &res, flag);
        }
    }
    return flag;
}

static char *alloc_flag(void)
{
    char *str = malloc(sizeof(char) * 6);

    for (int i = 0; i < 6; i++)
        str[i] = '\0';
    return str;
}

static char *clear_flag(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = '\0';
    return str;
}

int my_printf(char *s, ...)
{
    va_list ap;
    char *flag = alloc_flag();
    int cpt = 0;

    va_start(ap, s);
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '%') {
            my_putchar(s[i]);
            cpt ++;
        } else {
            clear_flag(flag);
            i += 1;
            flag = multi_flag(s, flag, &i);
            cpt = cpt + my_put_arg(ap, flag);
        }
    }
    free(flag);
    va_end(ap);
    return cpt - 1;
}
