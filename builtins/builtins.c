/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                              :+:      :+:    :+:  */
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
	//TODO error on extra arguments present
}

int	my_pwd(t_mshell *shell) //TODO error on extra arguments present
{
	t_list	*node;
	char	*curr_dir;

	curr_dir = NULL;
	node = get_by_key(shell, "PWD");
	if (!node || !((t_envvar *)(node->content))->value)
	{ /* in case pwd is unset, get the pwd from getcwd */
		curr_dir = getcwd(curr_dir, 1);
		if (!curr_dir)
		{
			print_error("pwd");
			shell->last_exit_code = 1;
			return (1);
		}
		printf("%s\n", curr_dir);
	}
	else
		printf("%s\n", ((t_envvar *)(node->content))->value);
	return (0);
}

void	my_exit(t_mshell *shell)
{ //TODO full memory clear, not only env (?)
	ft_lstclear(&shell->env_copy, free_node);
	exit(0);
}

//void	my_echo(t_mshell *shell, t_cmd *cmd) //additional arg is the
//// exec_cmd_struct
//{
//	if (!ft_strncmp(cmd->arg_arr[0], "-n", ft_strlen(cmd->arg_arr[0])))
//	{
//
//	}
//}