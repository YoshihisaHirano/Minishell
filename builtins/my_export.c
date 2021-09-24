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

char	**split_by_eq(char *arg)
{
	char	**var;
	int		i;

	var = malloc(sizeof(char *) * 3);
	if (!var)
		error_exit("export");
	i = 0;
	while (i < 3)
		var[i++] = NULL;
	i = 1;
	while (arg[i] != '=')
		i++;
	var[0] = ft_substr(arg, 0, i);
	if (ft_strlen(var[0]) == ft_strlen(arg))
		return (var);
	i++;
	arg += i;
	var[1] = ft_substr(arg, 0, ft_strlen(arg));
	return (var);
}

void	set_val(char **splt_arg, t_mshell *shell)
{
	t_list	*elt;

	elt = get_by_key(shell, splt_arg[0]);
	if (elt)
		set_by_key(shell, splt_arg[0], splt_arg[1]);
	else
		add_var(shell, splt_arg[0], splt_arg[1]);
}

// export can add multiple vars to environment if they are properly
//  formatted i.e. 'VAR_NAME=', vars with wrong format it just ignores
void	my_export(t_mshell *shell, char **cmd_arr)
{
	char	**splt_arg;
	char	*arg;
	int		i;

	i = 1;
	while (cmd_arr[i])
	{
		arg = cmd_arr[i];
		splt_arg = split_by_eq(arg);
		if (invalid_key(splt_arg[0]))
		{
			print_err_msg("export", arg, "not an identifier");
			i++;
			continue ;
		}
		shell->last_exit_code = 0;
		if (!splt_arg[1])
		{
			i++;
			continue ;
		}
		set_val(splt_arg, shell);
		free_arr(splt_arg);
		i++;
	}
}