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

}

int	my_unset(t_mshell *shell, char *arg)
{
	if (invalid_key(arg))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": invalid parameter name", 2);
		shell->last_exit_code = 1;
		return (1);
	}

	return (0);
}