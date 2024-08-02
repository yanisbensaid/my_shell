/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task01
*/

char *my_strcpy(char *dest, char const *src)
{
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}
