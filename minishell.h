#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/rltypedefs.h"
# include "libft/libft.h"
# define PROMPT "Minishell$ "

typedef struct s_envvar
{
	char	*key;
	char	*value;
} t_envvar;

typedef	struct	s_mshell
{
	t_list	*env_copy;
	int		last_exit_code;
} t_mshell;

typedef	struct	s_cmd
{
	t_mshell	*shell;
	char		**arg_arr;
} t_cmd;

void	handle_sigs(void);
void	error_exit(char *prog);
void	free_node(void *node);
void	print_node(void *node);
void	print_error(char *prog);
int		invalid_key(char *key);
void	free_arr(char **arr);
char	*expand_var(char *var, t_mshell *shell);
/* env manipulations */
void	parse_env(t_mshell *shell, char **env);
t_list	*get_by_key(t_mshell *shell, char *key);
int		set_by_key(t_mshell *shell, char *key, char *val);
char	**lst_to_arr(t_mshell *shell);
void	add_var(t_mshell *shell, char *key, char *val);
/* builtins */
void	my_env(t_mshell *shell);
int		my_pwd(t_mshell *shell);
int		my_cd(t_mshell *shell, char *path);
void	my_exit(t_mshell *shell);
int		my_export(t_mshell *shell, char *arg);
int		my_unset(t_mshell *shell, char *arg);

#endif
