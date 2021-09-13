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

typedef struct	s_quotes
{
	int	singl;
	int	doubl;
} t_quotes;

typedef	struct	s_mshell
{
	t_list	*env_copy;
	int		last_exit_code;
} t_mshell;

void	handle_sigs(void);
void	error_exit(char *prog);
void	free_node(void *node);
void	print_node(void *node);
void	print_error(char *prog);
int		invalid_key(char *key);
void	free_arr(char **arr);
void	move_spaces(char **str, char **start);
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
/* parsing */
int		check_quotes(char *str, t_mshell *shell);
void	remove_quotes(char **pre_res);
char	*add_expanded(char **start, char **str, char *res, t_mshell *shell);
char	*preprocessor(char *str, t_mshell *shell);

#endif
