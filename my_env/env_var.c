/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:44:39 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/05 18:44:39 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_env(t_mshell *shell, char **env)
{
	t_envvar	*var;
	t_list		*node;
	int			i;
	char		**str_var;

	i = 0;
	while (env[i])
	{
		var = malloc(sizeof(t_envvar));
		if (!var)
			error_exit();
		str_var = ft_split(env[i], '=');
		if (!str_var)
			error_exit();
		var = (t_envvar){.key = str_var[0], .value = str_var[1]};
		node = ft_lstnew(var);
		if (!node)
			error_exit();
		ft_lstadd_back(&shell->env_copy, node);
		i++;
	}
}