/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-minishell2-matteo.chapelle-esmel
** File description:
** my_realloc.c
*/

#include "../include/my.h"

void *my_realloc(void *re_ptr, int size)
{
    char *ptr_realloc = NULL;
    char *ptr = re_ptr;
    int c = 0;

    if (ptr == NULL || size < 1)
        return NULL;
    ptr_realloc = malloc(sizeof(char) * (size + 1));
    while (c != size && ptr[c] != '\0') {
        ptr_realloc[c] = ptr[c];
        c++;
    }
    if (ptr[c] == '\0')
        while (c < size) {
            ptr_realloc[c] = '\0';
            c++;
        }
    ptr_realloc[c] = '\0';
    free(ptr);
    return (void *)ptr_realloc;
}
