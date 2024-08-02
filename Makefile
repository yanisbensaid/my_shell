##
## EPITECH PROJECT, 2023
## minishell2
## File description:
## Makefile
##

NAME	=	42sh

LIB_NAME	=	libmy.a

SRCS	=	src/main.c \
			src/memalloc_2d_array.c \
			src/str_to_arr.c \
			src/concat_str.c \
			src/functions.c \
			src/my_isalphanum.c \
			src/ptr_funcs.c \
			src/env_functions.c \
			src/my_strdup.c \
			src/signal_handler.c \
			src/env_linked_list.c \
			src/binary_tree.c \
			src/exec_pipe.c \
			src/my_realloc.c \
			src/exec_redir.c \
			src/my_cd.c \
			src/exec_or.c \
			src/exec_and.c \
			src/exec_tree.c \
			src/aliases.c \
			src/alias_cmd.c \
			src/globbings.c \
			src/history.c \
			src/history_print.c \
			src/local_var.c \
			src/point_dexclamation.c \

LIB_SRCS	=	lib/my/my_putchar.c \
                			lib/my/my_putstr.c \
                			lib/my/my_put_nbr.c \
                			lib/my/my_strlen.c \
                			lib/my/my_strcat.c \
                			lib/my/my_strcpy.c \
                			lib/my/my_putnbr_base.c \
                			lib/my/my_compute_power_rec.c \
                			lib/my/my_printstr.c \
                			lib/my/my_printchar.c \
                			lib/my/my_print_nbr.c \
                			lib/my/my_printf.c \
                			lib/my/my_print_hexa.c \
                			lib/my/my_print_hexa_maj.c \
                			lib/my/my_print_octal.c	\
                			lib/my/my_printpourcent.c \
                			lib/my/my_printfloat.c \
                			lib/my/my_putfloat.c \
                			lib/my/my_revstr.c \
                			lib/my/my_strcmp.c \
                			lib/my/my_strncmp.c \
                			lib/my/my_print_unsigned_int.c \
                			lib/my/my_put_uint.c \
                			lib/my/my_printround.c \
                			lib/my/my_strncpy.c	\
                			lib/my/my_putfloat_supr.c	\
                			lib/my/my_printround_supr.c \
                			lib/my/my_printfloat_round.c \
                			lib/my/my_printdouble.c \
                			lib/my/my_printadd.c \
                			lib/my/my_getnbr.c

OBJS	=	$(SRCS:.c=.o)

LIB_OBJS	=	$(LIB_SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -g3

CPPFLAGS	=	-I./include

LDFLAGS		=	-L./ -lmy	-lncurses

all:	 $(LIB_NAME)	$(NAME)	clean

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS)

$(LIB_NAME):	$(LIB_OBJS)
	ar rc $(LIB_NAME) $(LIB_OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(LIB_OBJS)
	$(RM) *~
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB_NAME)

re:	fclean all
