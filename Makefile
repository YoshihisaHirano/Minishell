SRC		=	main.c signals.c utils.c env_var.c builtins/builtins.c builtins/my_cd.c builtins/my_export.c builtins/my_unset.c free.c parsing/parse_args.c parsing/expansion/expansion.c parsing/expansion/quotes.c parsing/expansion/preprocessor.c
PROG	=	minishell
LIBDIR	=	./libft
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -L readline/lib/ -lreadline -lhistory -L $(LIBDIR) -lft -g
HEADER	=	minishell.h

.PHONY	:	all re clean fclean

all		:	$(PROG)

$(LIB)	:
			make -s -C $(LIBDIR)

$(PROG)	:	$(HEADER) $(SRC) $(LIB)
			$(CC) $(CFLAGS) $(SRC) -o $(PROG)

clean	:
			rm -f $(PROG)
			make clean -C $(LIBDIR)

fclean	:
			make fclean -C $(LIBDIR)
			rm -f $(PROG)

re		:	fclean all