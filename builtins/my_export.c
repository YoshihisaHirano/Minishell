/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:28:18 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/07 18:28:18 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
!!! The correct syntax to export a variable (with whatever value, if any, it has
 already been assigned) is export NAME. //TODO ?
The correct syntax to assign and export a variable (with the assigned value) at the same time is export NAME=value
 */

// TODO export can add multiple vars to environment if they are properly
//  formatted i.e. 'VAR_NAME=', vars with wrong format it just ignores
int	my_export(t_mshell *shell, t_list_params *params)
{
	char	**splt_arg;
	t_list	*elt;
	char	*arg;

	arg = params->cmd_arr[1];
	splt_arg = ft_split(arg, '=');
	if (!splt_arg)
		error_exit(NULL);
	if (invalid_key(splt_arg[0]))
	{
		print_err_msg("export", arg, "not an identifier");
		shell->last_exit_code = 1;
		return (1);
	}
	elt = get_by_key(shell, splt_arg[0]);
	if (elt)
		set_by_key(shell, splt_arg[0], splt_arg[1]);
	else
		add_var(shell, splt_arg[0], splt_arg[1]);
	return (0);
}