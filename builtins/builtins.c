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

void	my_env(t_mshell *shell)
{
	ft_lstiter(shell->env_copy, print_node);
	//TODO error on extra arguments present ???
}

int	my_pwd(t_mshell *shell)
{
	t_list	*node;
	char	*curr_dir;

	curr_dir = NULL;
	node = get_by_key(shell, "PWD");
	if (!node || !((t_envvar *)(node->content))->value
		|| !(((t_envvar *)(node->content))->value[0]))
	{ /* in case pwd is unset, get the pwd from getcwd */
		curr_dir = getcwd(curr_dir, 1);
		if (!curr_dir)
		{
			print_error("pwd", shell);
			return (1);
		}
		printf("%s\n", curr_dir);
	}
	else
		printf("%s\n", ((t_envvar *)(node->content))->value);
	return (0);
}

void	my_echo(t_mshell *shell, t_list_params *params)
{
	char	*option;
	int		i;
	int		new_line;

	option = params->cmd_arr[1];
	i = 1;
	new_line = 1;
	if (!ft_strncmp("-n", option, ft_strlen(option)))
	{
		new_line = 0;
		i++;
	}
	while (i < chr_arr_len(params->cmd_arr) - 1)
	{
		printf("%s ", params->cmd_arr[i]);
		i++;
	}
	printf("%s", params->cmd_arr[i]);
	if (new_line)
		printf("\n");
}