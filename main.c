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

int	g_last_exit_code = 0;

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
		g_last_exit_code = 127;
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
	printf("%s\n", temp2);
	pid = fork();
	if (pid == 0)
	{
		int j = execve(temp2, cmd_arr, lst_to_arr(shell));
		printf("%d - status code, %d - errno\n", j, errno);
		perror("");
		exit(256);
	}
	else
		waitpid(pid, &g_last_exit_code, 0);
}

void	execute(char *cmd_str, t_mshell *shell)
{
	t_list			*list;
	char			**envp;

	envp = lst_to_arr(shell);
//	ft_putstr_fd(copy_str, 1);
//	ft_putstr_fd("\n", 1);
	list = NULL;
	parser(cmd_str, &list, shell);
//	ft_putstr_fd("parser\n", 1);
	validation(list, envp);
//	ft_putstr_fd("validation\n", 1);
	show_params(list);
	if (((t_list_params *)(list->content))->builtin != NULL)
		((t_list_params *)(list->content))->builtin(shell, (t_list_params *)(list->content));
//	ft_putstr_fd("free\n", 1);
	free_arr(envp);
	ft_lstclear(&list, free_params_lst);
//	ft_lstclear(&shell->env_copy, free_node);
	/*builtin = check_builtins(shell, cmd_arr);
	if (builtin)
		return ;
	run_command(shell, cmd_arr);*/
}

int main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;
	char		*untrimmed;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
//	char *cmd_str = "echo -n \"cat -e\" hello $World $HOME";
//	execute(cmd_str, &shell);
//	return (0);
////	str = "echo hello >lol echo > test>lol>test>>lol>test mdr >lol test >test";
////	execute(ft_strdup(str), &shell);
	while(1)
	{
		untrimmed = readline(PROMPT);
		str = ft_strtrim(untrimmed, " \t");
		if (str && *str)
		{
			add_history(str);
			execute(str, &shell);
		}
		if (!str) //Ctrl-d handling lol
		{ //TODO need to put "exit" message on the same line with the prompt ???
			exit_routine(&shell);
			exit(g_last_exit_code);
		}
		free(untrimmed);
		free(str);
	}
	return (0);
}
