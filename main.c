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

void	init_shell(t_mshell *shell, char **env)
{
	*shell = (t_mshell){.last_exit_code = 0, .env_copy = NULL};
	parse_env(shell, env);
//	handle_sigs();
}

int main(int argc, char **argv, char **env)
{
	char		*str;
	t_mshell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
//	my_env(&shell);
//	printf("\n");
//	my_export(&shell, "ARG=5");
//	my_env(&shell);
//	printf("\n");
//	my_unset(&shell, "HOME");
//	my_env(&shell);
//	my_pwd(&shell);
//	my_cd(&shell, "..");
//	printf("\n --------------- \n");
//	my_env(&shell);
//	printf("\n");
//	my_pwd(&shell);
//	my_cd(&shell, "..");
//	printf("\n --------------- \n");
//	my_env(&shell);
//	printf("\n");
//	my_pwd(&shell);
//	char **spltstr = ft_split("PATH", '=');
//	printf("%s, %p\n", spltstr[0], spltstr[1]);
	str = expand_var(ft_strdup("$?"), &shell);
	printf("%s\n", str);
	free(str);
	str = expand_var(ft_strdup("HELLO$?"), &shell);
	printf("%s\n", str);
	free(str);
	str = expand_var(ft_strdup("HELLO$HOME"), &shell);
	printf("%s\n", str);
	free(str);
	str = expand_var(ft_strdup("HELLO\'$HOME\'"), &shell);
	printf("%s\n", str);
	free(str);
	str = expand_var(ft_strdup("O$HOME"), &shell);
	printf("%s\n", str);
	free(str);
	str = expand_var(ft_strdup("O\'$H\'OME"), &shell);
	printf("%s\n", str);
	free(str);
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