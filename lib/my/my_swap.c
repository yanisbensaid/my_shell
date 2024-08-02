/*
** EPITECH PROJECT, 2023
** day04
** File description:
** task01
*/

#include <unistd.h>

void my_swap(int *a, int *b)
{
    int c = *b;

    *b = *a;
    *a = c;
}
