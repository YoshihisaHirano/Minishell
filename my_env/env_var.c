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
			error_exit(NULL);
		str_var = ft_split(env[i], '=');
		if (!str_var)
			error_exit(NULL);
		*var = (t_envvar){.key = str_var[0], .value = str_var[1]};
		node = ft_lstnew(var);
		if (!node)
			error_exit(NULL);
		ft_lstadd_back(&shell->env_copy, node);
		free_arr(str_var, 2);
		i++;
	}
}

t_list	*get_by_key(t_mshell *shell, char *key)
{
	t_list	*temp;
	char	*node_key;

	temp = shell->env_copy;
	while (temp)
	{
		node_key = ((t_envvar *)(temp->content))->key;
		if (!ft_strncmp(node_key, key, ft_strlen(node_key)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

//void	set_by_key(t_mshell *shell, char *key, char *val)