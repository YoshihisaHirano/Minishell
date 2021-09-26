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

void	execute(char *cmd_str, t_mshell *shell)
{
	char	**cmd_arr;
	int		builtin;

	cmd_arr = parse_args(cmd_str, shell);
	builtin = check_builtins(shell, cmd_arr);
	if (builtin)
		return ;

}

int main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;

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
		else if (!str) //Ctrl-d handling lol
		{ //TODO need to put "exit" message on the same line with the prompt
			exit_routine(&shell);
			exit(shell.last_exit_code);
		}
	}
	return (0);
}