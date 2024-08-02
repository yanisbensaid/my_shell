/*
** EPITECH PROJECT, 2023
** B-PSU-100-MPL-1-1-sokoban-matteo.chapelle-esmel
** File description:
** my.h
*/

#pragma once

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <ncurses.h>
#include <stdint.h>
#include "my_printf.h"
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <ncurses.h>
#include <glob.h>
#include <term.h>
#include <time.h>
#include <ctype.h>

enum Types {
    NONE = 0,
    CMD,
    SEP,
    PIPE,
    L_REDIR,
    L_REDIR2,
    R_REDIR,
    R_REDIR2,
    OR,
    AND
};

typedef struct history_s {
    char *command;
    char *time;
    int index;
    struct history_s *next;
} history_t;

typedef struct alias_s {
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

typedef struct list_s {
    char *data;
    struct list_s *next;
    int type;
    int local;
} list_t;

typedef struct binary_tree_s {
    char *data;
    enum Types type;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
} binary_tree_t;

char **char_alloc_2d_array(int, int);
char **str_to_arr(char *, char *);
char **split_string_tok(char *);
char *concat_strings(const char *, const char *);
int check_path(char *);
int parse(char *, char **, int);
int correct_path(char *, char **, char **);
int check_ptr_funcs(char *, char **, char **);
int exec_command(char **, char *, char **);
int my_putfd(int, char *);
int arr_len(char **);
int my_cd(char *, char **, char **);
int my_echo(char **);
int *get_bool(void);
int exit_shell(void);
int printenv(void);
char *get_env_var(char *);
char *find_executable(char *);
char *my_strdup(const char *);
void sigint_handler(int);
int my_strncmp_env(char const *, char const *, int);
list_t *parse_env_to_list(char **);
void append_node(list_t **, char *, int);
list_t **get_env(char **);
int my_unsetenv(char **);
int my_setenv(char **);
void free_list(void);
int free_mem(char **);
void my_memory_set(void *, int, size_t);
char *get_path_var(char *);
char *my_strsignal(int);
void *my_realloc(void *, int);
char *my_strchr(const char *, int);
int b_tree(char *, char **);
void free_tree(binary_tree_t *);
int exec_tree(binary_tree_t *, char **);
int execute_pipe_operation(binary_tree_t *, char **);
void parse_command_line(char *, binary_tree_t *);
void create_pipe_node(binary_tree_t *, char **, int);
void create_sep_node(binary_tree_t *, char **, int);
char **str_to_arr2(const char *, const char *);
binary_tree_t *create_node(void);
char *clean_str(char *, char);
char *construct_command(char **, int, int);
void create_redir_node(binary_tree_t *, char **, int, char);
void create_redir2_node(binary_tree_t *, char **, int, char);
int execute_redirect_operation(binary_tree_t *, char **);
void create_or_node(binary_tree_t *, char **, int);
void create_and_node(binary_tree_t *, char **, int);
int exec_or(binary_tree_t *, char **);
int exec_and(binary_tree_t *, char **);
alias_t *parse_aliases(void);
alias_t *get_alias_list(alias_t *, int);
char *check_alias(char **);
void free_aliases(void);
int print_aliases(void);
void add_alias(alias_t **, char *, char **);
int alias(char **);
char **my_arrdup(char **);
int unalias(char **);
void *my_calloc(size_t, size_t);
char *glob_pattern(char *);
char **check_globbings(char **);
history_t *get_history(history_t *);
void parse_history(void);
int print_history(char **);
void write_to_history(char *, int);
void free_history(void);
int re_alias(void);
int print_history_borned(int, history_t *);
history_t *reverse_history(history_t *);
void print_history_entry(history_t *);
int my_setlocal(char **);
int printlocal(void);
void replace_value(list_t *, char *);
int unset_local(char **);
int my_isalnum(int);
char **point_dexclamation(char **);

// Define ANSI escape codes for text colors
#define RESET   "\x1B[0m"
#define BLACK   "\x1B[30m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

// Define ANSI escape codes for lighter text colors
#define LBLACK   "\x1B[90m"
#define LRED     "\x1B[91m"
#define LGREEN   "\x1B[92m"
#define LYELLOW  "\x1B[93m"
#define LBLUE    "\x1B[94m"
#define LMAGENTA "\x1B[95m"
#define LCYAN    "\x1B[96m"
#define LWHITE   "\x1B[97m"

// Define ANSI escape codes for text styles
#define BOLD      "\x1B[1m"
#define DIM       "\x1B[2m"
#define UNDERLINE "\x1B[4m"
#define BLINK     "\x1B[5m"
#define REVERSE   "\x1B[7m"
#define HIDDEN    "\x1B[8m"
