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
	while (arg[i] && arg[i] != '=')
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

void	appending(void *content, char *add_value)
{
	char		*temp;
	t_envvar	*var;

	var = (t_envvar *)content;
	if (!var->value)
		var->value = add_value;
	else
	{
		temp = ft_strjoin(var->value, add_value);
		free(var->value);
		var->value = temp;
	}
}

int	append_val(char **splt_arg, t_mshell *shell, char *arg)
{
	char	*temp;
	size_t 	last_elt;
	t_list	*elt;

	if (ft_strlen(splt_arg[0]) <= 1)
		return (0);
	last_elt = ft_strlen(splt_arg[0]) - 1;
	if (splt_arg[0][last_elt] != '+')
		return (0);
	temp = ft_substr(splt_arg[0], 0, last_elt);
	if (invalid_key(temp))
	{
		print_err_msg("export", arg, "not a valid identifier");
		return (1);
	}
	elt = get_by_key(shell, temp);
	if (!elt)
		add_var(shell, temp, splt_arg[1]);
	else
		appending(elt->content, splt_arg[1]);
	free(temp);
	return (1);
}

// export can add multiple vars to environment if they are properly
//  formatted i.e. 'VAR_NAME=', vars with wrong format it just ignores
void	my_export(t_mshell *shell, char **cmd_arr)
{
	char	**splt_arg;
	char	*arg;
	int		i;

	i = 0;
	while (cmd_arr[++i])
	{
		arg = cmd_arr[i];
		splt_arg = split_by_eq(arg);
		if (append_val(splt_arg, shell, arg))
			continue ;
		if (invalid_key(splt_arg[0]))
		{
			print_err_msg("export", arg, "not a valid identifier");
			continue ;
		}
		last_exit_code = 0;
		if (!splt_arg[1])
			continue ;
		set_val(splt_arg, shell);
		free_arr(splt_arg);
	}
}