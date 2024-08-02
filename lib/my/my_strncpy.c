/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task02
*/

char *my_strncpy(char *dest, const char *src, int n)
{
    int i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
