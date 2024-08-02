/*
** EPITECH PROJECT, 2023
** day05
** File description:
** task05
*/

int my_compute_square_root(int nb)
{
    int root = 1;

    if (nb == 0) {
        return 0;
    }
    while (root <= nb) {
        if (root * root == nb) {
            return root;
        }
        root ++;
    }
    return 0;
}
