/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task06
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    if (s1[i] - s2[i] > 0) {
        return 1;
    } else if (s1[i] - s2[i] < 0) {
        return -1;
    } else {
        return 0;
    }
}
