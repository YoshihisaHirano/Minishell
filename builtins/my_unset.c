/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:23:36 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/08 18:23:36 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_var(t_mshell *shell, t_list *node)
{
	t_list	*before_del;
	t_list	*after_del;

	before_del = shell->env_copy;
	while (before_del->next != node)
		before_del = before_del->next;
	after_del = node->next;
	ft_lstdelone(node, free_node);
	before_del->next = after_del;
}

int	my_unset(t_mshell *shell, char *arg)
{
	t_list	*var;

	if (invalid_key(arg))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": invalid parameter name", 2);
		shell->last_exit_code = 1;
		return (1);
	}
	var = get_by_key(shell, arg);
	if (!var)
	{
		shell->last_exit_code = 1;
		return (1);
	}
	del_var(shell, var);
	return (0);
}