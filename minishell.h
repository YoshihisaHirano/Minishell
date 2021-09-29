#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include "readline.h"
# include "history.h"
# include "rltypedefs.h"
# define ARG_OK 1
# define NOT_NUMERIC 2
# define PROMPT "Minishell$ "

typedef struct s_envvar
{
	char	*key;
	char	*value;
}	t_envvar;

typedef struct s_quotes
{
	int	singl;
	int	doubl;
}	t_quotes;

typedef struct s_list_params
{
	char	**cmd_arr;
	char	*str_to_cmd;
	char	*path_app;
	int		fd[2];
	char	*here_doc_limiter;
	int		input_mod;
	int		output_mode;
	char	*input_file;
	char	*output_file;
}			t_list_params;

typedef struct s_mshell
{
	t_list			*env_copy;
	int				last_exit_code;
	t_list			*cmds;
	t_list			*builtins;
}	t_mshell;

typedef struct s_builtins
{
	char	*name;
	void	(*func)(t_mshell *, char **);
}	t_builtins;

void		handle_sigs(void);
void		error_exit(char *prog);
void		free_node(void *node);
void		free_params_lst(void *param_node);
void		free_builtins(void *content);
void		print_node(void *node);
void		print_error(char *prog, t_mshell *shell, char *arg);
int			invalid_key(char *key);
void		free_arr(char **arr);
void		move_spaces(char **str, char **start);
void		print_err_msg(char *prog, char *arg, char *msg);
size_t		chr_arr_len(char **arr);
long long	ft_atoi_ll(const char *nptr);
void		init_shell(t_mshell *shell, char **env);
void		exit_routine(t_mshell *shell);
/* env manipulations */
void		parse_env(t_mshell *shell, char **env);
t_list		*get_by_key(t_mshell *shell, char *key);
int			set_by_key(t_mshell *shell, char *key, char *val);
char		**lst_to_arr(t_mshell *shell);
void		add_var(t_mshell *shell, char *key, char *val);
/* builtins */
void		my_env(t_mshell *shell, char **cmd_arr);
void		my_pwd(t_mshell *shell, char **cmd_arr);
void		my_cd(t_mshell *shell, char **cmd_arr);
void		my_export(t_mshell *shell, char **cmd_arr);
void		my_unset(t_mshell *shell, char **cmd_arr);
void		my_exit(t_mshell *shell, char **cmd_arr);
void		my_echo(t_mshell *shell, char **cmd_arr);
/* parsing */
int			check_quotes(char *str, t_mshell *shell);
char		*remove_quotes(char *pre_res);
char		*add_expanded(char **start, char **str, char *res, t_mshell *shell);
char		*preprocessor(char *str, t_mshell *shell);
char		**parse_args(char *args, t_mshell *shell);

#endif
