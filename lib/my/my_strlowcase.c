/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task09
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 65 && str[i] < 90) {
            str[i] = str[i] + 32;
        }
    }
    return str;
}
