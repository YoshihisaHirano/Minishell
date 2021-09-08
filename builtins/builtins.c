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

void	my_pwd(t_mshell *shell) //TODO error on extra arguments present
{
	t_list	*node;

	node = get_by_key(shell, "PWD");
	if (((t_envvar *)(node->content))->value)
		printf("%s\n", ((t_envvar *)(node->content))->value);
	else //in case pwd is unset, get the pwd from getcwd
		printf("\n");
}

void	my_exit(t_mshell *shell) //TODO full memory clear, not only env
{
	ft_lstclear(&shell->env_copy, free_node);
	exit(0);
}
