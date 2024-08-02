/*
** EPITECH PROJECT, 2023
** B-CPE-110-MPL-1-1-bssettingup-matteo.chapelle-esmel
** File description:
** memalloc_2d_array.c
*/

#include "my.h"

void my_memset(void *ptr, int value, size_t num_bytes)
{
    unsigned char *p = ptr;

    for (size_t i = 0; i < num_bytes; i++) {
        *p = (unsigned char)value;
        p++;
    }
}

void *my_calloc(size_t num, size_t size)
{
    void *ptr = malloc(num * size);

    if (ptr) {
        my_memset(ptr, 0, num * size);
    }
    return ptr;
}

int **int_alloc_2d_array(int nb_rows, int nb_cols)
{
    int **buff = malloc(sizeof(int *) * (nb_rows + 1));

    for (int i = 0; i < nb_rows; i++) {
        buff[i] = malloc(sizeof(int) * (nb_cols + 1));
        for (int j = 0; j < nb_cols; j++) {
            buff[i][j] = 0;
        }
        buff[i][nb_cols] = 0;
    }
    buff[nb_rows] = NULL;
    return buff;
}

char **char_alloc_2d_array(int nb_rows, int nb_cols)
{
    char **buff = NULL;

    buff = malloc(sizeof(char *) * (nb_rows + 1));
    buff[nb_rows] = NULL;
    for (int i = 0; i < nb_rows; i++) {
        buff[i] = malloc(sizeof(char) * (nb_cols + 1));
        my_memset(buff[i], '\0', nb_cols + 1);
    }
    return buff;
}
