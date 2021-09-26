SRC		=	main.c signals.c env_var.c builtins/builtins.c builtins/my_cd.c builtins/my_export.c builtins/my_unset.c\
			utils/free.c parsing/parse_args.c parsing/expansion/expansion.c parsing/expansion/quotes.c parsing/expansion/preprocessor.c\
			utils/ft_atoi_ll.c utils/miscellaneous.c utils/print.c builtins/my_exit.c initialization.c
OBJ		=	$(SRC:.c=.o)
PROG	=	minishell
LIBDIR	=	./libft
RLDIR	=	/Users/$(USER)/.brew/opt/readline/include/readline
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -I$(RLDIR)
LFLAGS	=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory -L $(LIBDIR) -lft
HEADER	=	minishell.h

.PHONY	:	all re clean fclean

all		:	$(PROG)

$(LIB)	:
			make -s -C $(LIBDIR)

$(PROG)	:	$(HEADER) $(OBJ) $(LIB)
			$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(PROG)

%.o		:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)
			make clean -C $(LIBDIR)

fclean	:	clean
			make fclean -C $(LIBDIR)
			rm -f $(PROG)

re		:	fclean all