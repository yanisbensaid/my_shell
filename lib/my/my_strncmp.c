/*
** EPITECH PROJECT, 2023
** day06
** File description:
** task07
*/

int my_strncmp_env(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] == s2[i] && n > 1) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
        n--;
    }
    if (s1[i] - s2[i] > 0 || s1[i + 1] != '=')
        return 1;
    if (s1[i] - s2[i] < 0) {
        return -1;
    }
    return 0;
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] == s2[i] && n > 1) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
        n--;
    }
    if (s1[i] - s2[i] > 0) {
        return 1;
    } else if (s1[i] - s2[i] < 0) {
        return -1;
    } else {
        return 0;
    }
}
