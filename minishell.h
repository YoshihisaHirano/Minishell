#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/rltypedefs.h"
# include "libft/libft.h"
# define PROMPT "Minishell$ "

typedef struct s_envvar
{
	char				*key;
	char 				*value;
} t_envvar;

typedef	struct	s_mshell
{
	t_list	*env_copy;
	int		last_exit_code;
} t_mshell;

void	handle_sigs(void);
void	error_exit(char *prog);
void	free_arr(char **arr, int size);
void	print_node(void *node);
void	parse_env(t_mshell *shell, char **env);
void	my_env(t_mshell *shell);
t_list	*get_by_key(t_mshell *shell, char *key);

#endif
