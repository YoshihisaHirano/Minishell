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

void	my_unset(t_mshell *shell, char **cmd_arr)
{
	t_list	*var;
	char	*arg;
	int		i;

	i = 1;
	while (cmd_arr[i])
	{
		arg = cmd_arr[i];
		if (invalid_key(arg))
		{
			print_err_msg("unset", arg, "invalid parameter name");
			shell->last_exit_code = 1;
		}
		var = get_by_key(shell, arg);
		if (var)
		{
			del_var(shell, var);
			shell->last_exit_code = 0;
		}
		i++;
	}
}