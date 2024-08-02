/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-matteo.chapelle-esmel
** File description:
** point_dexclamation
*/

#include "../include/my.h"


history_t *find_matching_command(history_t *history, const char *search_string)
{
    history_t *current = history;
    history_t *temp = NULL;

    while (current != NULL) {
        if (strncmp(current->command, search_string,
            strlen(search_string)) == 0) {
            temp = current;
        }
        current = current->next;
    }
    return temp;
}

char **update_arr_with_matching_command(char **arr,
    history_t *matching_command)
{
    char *command = my_strdup(matching_command->command);
    char **new_arr = str_to_arr(command, " ");

    free_mem(arr);
    free(command);
    return new_arr;
}

char **point_dexclamation(char **arr)
{
    char *search_string = arr[0] + 1;
    history_t *history = get_history(NULL);
    history_t *matching_command = NULL;

    if (history == NULL) {
        my_printf("History is empty.\n");
        return arr;
    }
    matching_command = find_matching_command(history, search_string);
    if (matching_command == NULL) {
        my_printf("%s: Event not found.\n", search_string);
        return NULL;
    }
    my_printf("%s\n", matching_command->command);
    arr = update_arr_with_matching_command(arr, matching_command);
    return arr;
}
