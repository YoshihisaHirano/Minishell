/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:26:58 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/07 16:26:58 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_env(t_mshell *shell, char **cmd_arr)
{
	(void)cmd_arr;
	ft_lstiter(shell->env_copy, print_node);
	shell->last_exit_code = 0;
	//TODO error on extra arguments present ???
}

void	my_pwd(t_mshell *shell, char **cmd_arr)
{
	t_list	*node;
	char	*curr_dir;

	(void)cmd_arr;
	curr_dir = NULL;
	node = get_by_key(shell, "PWD");
	if (!node || !((t_envvar *)(node->content))->value
		|| !(((t_envvar *)(node->content))->value[0]))
	{ /* in case pwd is unset, get the pwd from getcwd */
		curr_dir = getcwd(curr_dir, 1);
		if (!curr_dir)
		{
			print_error("pwd", shell, NULL);
			return ;
		}
		printf("%s\n", curr_dir);
	}
	else
		printf("%s\n", ((t_envvar *)(node->content))->value);
	shell->last_exit_code = 0;
}

void	my_echo(t_mshell *shell, char **cmd_arr)
{
	char	*option;
	size_t	i;
	int		new_line;

	i = 1;
	option = cmd_arr[i];
	new_line = 1;
	while (!ft_strncmp("-n", option, ft_strlen(option)))
	{
		new_line = 0;
		i++;
		option = cmd_arr[i];
	}
	while (i < chr_arr_len(cmd_arr) - 1)
	{
		printf("%s ", cmd_arr[i]);
		i++;
	}
	printf("%s", cmd_arr[i]);
	if (new_line)
		printf("\n");
	shell->last_exit_code = 0;
}