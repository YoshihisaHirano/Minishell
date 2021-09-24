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

void	execute_builtins(char *cmd_str, t_mshell *shell)
{
	char	**cmd_arr;
	int		builtin;

	cmd_arr = parse_args(cmd_str, shell);
	builtin = check_builtins(shell, cmd_arr[0]);

}

int main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);

	return (0);
	while(1)
	{
		str = readline(PROMPT);
		if (str && *str)
			add_history(str);
		else if (!str) //Ctrl-d handling lol
		{
			ft_lstclear(&(shell.env_copy), free_node);
			rl_clear_history();
			exit(0);
		}
	}
	return (0);
}