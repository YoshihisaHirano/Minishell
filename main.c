/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:55:17 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/01 18:55:17 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_exit_code = 0;

int	check_builtins(t_mshell *shell, char **cmd_arr)
{
	t_list		*temp;
	t_builtins	*bn;

	temp = shell->builtins;
	while (temp)
	{
		bn = (t_builtins *)temp->content;
		if (!ft_strncmp(bn->name, cmd_arr[0], ft_strlen(cmd_arr[0])))
		{
			bn->func(shell, cmd_arr);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	run_command(t_mshell *shell, char **cmd_arr)
{
	t_list		*path_var;
	char		**path_arr;
	int			i;
	struct stat	buf;
	int			res;
	char		*temp;
	char		*temp2;
	int			pid;

	path_var = get_by_key(shell, "PATH");
	if (!path_var)
	{
		print_err_msg(NULL, cmd_arr[0], "No such file or directory");
		last_exit_code = 127;
		return ;
	}
	path_arr = ft_split(((t_envvar *)(path_var->content))->value, ':');
	i = 0;
	while (path_arr[i])
	{
		temp = ft_strjoin(path_arr[i], "/");
		temp2 = ft_strjoin(temp, cmd_arr[0]);
		res = lstat(temp2, &buf);
		free(temp);
		if (res != -1)
			break;
		free(temp2);
		i++;
	}
	if (!(path_arr[i]))
	{
		print_err_msg(NULL, cmd_arr[0], "command not found");
		return ;
	}
	pid = fork();
	if (pid == 0)
		execve(temp2, cmd_arr, lst_to_arr(shell));
	else
		waitpid(pid, &last_exit_code, 0);
}

void	execute(char *cmd_str, t_mshell *shell)
{
	char	**cmd_arr;
	int		builtin;

	cmd_arr = parse_args(cmd_str, shell);
	builtin = check_builtins(shell, cmd_arr);
	if (builtin)
		return ;
	run_command(shell, cmd_arr);
}

int main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;
	int			exit_code;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
//	char *cmd_str = "echo -n \"cat -e\" hello $World $HOME";
//	execute(cmd_str, &shell);
//	return (0);
	while(1)
	{
		str = readline(PROMPT);
		if (str && *str)
		{
			execute(str, &shell);
			add_history(str);
		}
		if (!str) //Ctrl-d handling lol
		{ //TODO need to put "exit" message on the same line with the prompt ???
			exit_code = last_exit_code;
			exit_routine(&shell);
			exit(exit_code);
		}
	}
	return (0);
}