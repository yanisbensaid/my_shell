/*
** EPITECH PROJECT, 2023
** B-CPE-101-MPL-1-1-myprintf-matteo.chapelle-esmel
** File description:
** my_put_nbr_base
*/

#include "../../include/my_printf.h"

int my_putnbr_base(int nbr, char const *base)
{
    int index;
    char res[1000] = {0};

    if (nbr < 0){
        my_putchar(45);
        my_putnbr_base(nbr * -1, base);
    }
    for (int i = 0; nbr > 0; i++) {
        index = nbr % my_strlen(base);
        res[i] = base[index];
        nbr = nbr / my_strlen(base);
    }
    my_putstr(my_revstr(res));
    return 0;
}

int my_put_luint_base(unsigned long int nbr, char const *base)
{
    int cpt = 0;
    int index;
    int len = my_strlen(base);

    index = nbr % len;
    nbr = nbr / len;
    if (nbr > 0) {
        my_put_luint_base(nbr, base);
    }
    cpt += my_putchar(base[index]);
    return cpt;
}

int my_put_luint_base_va_list(va_list ap)
{
    int cpt = 0;
    unsigned long int nb = va_arg(ap, unsigned long int);

    cpt += my_put_luint_base(nb, "0123456789abcdef");
    return cpt;
}
