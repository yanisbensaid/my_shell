/*
** EPITECH PROJECT, 2023
** day05
** File description:
** task06
*/

int my_is_prime(int nb)
{
    int d = 2;

    if (nb <= 1) {
        return 0;
    }
    while (nb > d) {
        if (nb % d == 0) {
            return 0;
        }
        d++;
    }
    return 1;
}
