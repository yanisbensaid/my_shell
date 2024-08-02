/*
** EPITECH PROJECT, 2024
** Epitech_42sh
** File description:
** globbings.c
*/

#include "../include/my.h"

static char **replace_with_globbings(char **globbings, char **input, int i)
{
    int glob_len = arr_len(globbings);
    int input_len = arr_len(input);
    char **new_input = malloc(sizeof(char *) * (input_len + glob_len + 1));
    int j = 0;
    int k;

    for (; j < i; j++)
        new_input[j] = my_strdup(input[j]);
    for (k = 0; globbings[k] != NULL; k++) {
        new_input[j] = my_strdup(globbings[k]);
        j++;
    }
    for (k = i + 1; input[k] != NULL; k++) {
        new_input[j] = my_strdup(input[k]);
        j++;
    }
    new_input[j] = NULL;
    new_input[j] = NULL;
    free_mem(input);
    return new_input;
}

static char *process_wildcard(char *wildcard, char *processed_wildcard,
    char *pw_ptr, int in_quotes)
{
    int escaped = 0;

    for (char *wc_ptr = wildcard; *wc_ptr != '\0'; wc_ptr++) {
        if (*wc_ptr == '\\') {
            escaped = 1;
            continue;
        }
        if (*wc_ptr == '"' || *wc_ptr == '\'') {
            in_quotes = !in_quotes;
            continue;
        }
        if ((*wc_ptr == '*' || *wc_ptr == '?') && (in_quotes || escaped)) {
            *pw_ptr = '\\';
            pw_ptr++;
        }
        *pw_ptr = *wc_ptr;
        pw_ptr++;
        escaped = 0;
    }
    return processed_wildcard;
}

glob_t get_glob_results(char *processed_wildcard)
{
    glob_t glob_results;

    glob(processed_wildcard, GLOB_NOCHECK, 0, &glob_results);
    return glob_results;
}

char *concatenate_glob_results(glob_t glob_results)
{
    size_t length = 0;
    char *gfilename = NULL;

    for (size_t i = 0; i < glob_results.gl_pathc; i++)
        length += my_strlen(glob_results.gl_pathv[i]) + 1;
    gfilename = my_calloc(length, sizeof(char));
    for (size_t i = 0; i < glob_results.gl_pathc; i++) {
        my_strcat(gfilename, glob_results.gl_pathv[i]);
        if (i < glob_results.gl_pathc - 1)
            my_strcat(gfilename, " ");
    }
    return gfilename;
}

char *glob_pattern(char *wildcard)
{
    char *gfilename = NULL;
    char *buff = my_calloc(my_strlen(wildcard) + 1, sizeof(char));
    char *pw_ptr = buff;
    char *processed_wildcard = process_wildcard(wildcard, buff, pw_ptr, 0);
    glob_t glob_results = get_glob_results(processed_wildcard);

    gfilename = concatenate_glob_results(glob_results);
    globfree(&glob_results);
    free(processed_wildcard);
    return gfilename;
}

char **check_globbings(char **arr)
{
    char **new_arr = NULL;
    char *gfilename = NULL;
    char **globbings = NULL;
    int i = 0;

    for (; arr[i] != NULL; i++) {
        if (my_strchr(arr[i], '*') != NULL || my_strchr(arr[i], '?') != NULL
            || my_strchr(arr[i], '[') != NULL
            || my_strchr(arr[i], ']') != NULL) {
            gfilename = glob_pattern(arr[i]);
            globbings = str_to_arr(gfilename, " ");
            new_arr = replace_with_globbings(globbings, arr, i);
            free(gfilename);
            free_mem(globbings);
            return new_arr;
        }
    }
    return arr;
}
