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
//	str = expand_var(ft_strdup("$?"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("HELLO$?"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("HELLO$HOME"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("HELLO$HOMEHOHO"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("HELLO\'$HOME\'"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("O$HOME"), &shell);
//	printf("%s\n", str);
//	free(str);
//	str = expand_var(ft_strdup("O\'$H\'OME"), &shell);
//	printf("%s\n", str);
//	free(str);
//	char **arr = ft_split("echo -n \"cat -e\"$H'O'ME$USER", '\'');
//	int i = 0;
//	while (arr[i])
//	{
//		printf("%s\n", arr[i]);
//		i++;
//	}
//	printf("\n");
//	char **dq = ft_split(arr[0], '\"');
//	i = 0;
//	while (dq[i])
//	{
//		printf("%s\n", dq[i]);
//		i++;
//	}
	char *str1 = "echo    \'$HOME     $\'  '\"$USER\"'";
//	char *res = preprocessor(str1, &shell);
//	printf("%s\n", res);
	char **res = parse_args(str1, &shell);
	int i = 0; // debug
	while (res[i])
	{
		printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	ft_lstclear(&shell.env_copy, free_node);
	free(res);
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