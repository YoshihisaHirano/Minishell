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

void	my_export(t_mshell *shell, char *arg)
{
	t_list		*node;
	t_envvar	*var;
	char		**key_val;

	//format checking is necessary
	key_val = ft_split(arg, '=');
	if (!key_val)
		error_exit("export");
	node = get_by_key(shell, arg);
	if (!node)
	{
		var = malloc(sizeof(t_envvar));
		if (!var)
			error_exit("export");
		*var = (t_envvar){.key = key_val[0], .value = key_val[1]};
	}
	else
		((t_envvar *)(node->content))->value = key_val[1];
}