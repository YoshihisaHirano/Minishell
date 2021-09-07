SRC		=	main.c signals.c errors.c my_env/env_var.c
PROG	=	minishell
LIBDIR	=	./libft
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -L readline/lib/ -lreadline -lhistory -L $(LIBDIR) -lft
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