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
		str = ft_strtrim(untrimmed, " \t"); // all spaces from isspace?
		if (str && *str)
		{
			add_history(str);
//			execute(str, &shell);
			execution(str, &shell);
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
