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
{ //TODO is it necessary to do something with "_" env variable?
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
		free(str_var);
		i++;
	}
}

t_list	*get_by_key(t_mshell *shell, char *key)
{
	t_list	*temp;
	char	*curr_key;

	temp = shell->env_copy;
	while (temp)
	{
		curr_key = ((t_envvar *)(temp->content))->key;
		if (!ft_strncmp(curr_key, key, ft_strlen(curr_key))
			&& !ft_strncmp(curr_key, key, ft_strlen(key)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	set_by_key(t_mshell *shell, char *key, char *val) /* returns 0 on success */
{
	t_list		*temp;
	char		*curr_key;
	t_envvar	*curr_var;

	temp = shell->env_copy;
	while (temp)
	{
		curr_var = (t_envvar *)(temp->content);
		curr_key = curr_var->key;
		if (!ft_strncmp(curr_key, key, ft_strlen(curr_key))
			&& !ft_strncmp(curr_key, key, ft_strlen(key)))
		{
			if (curr_var->value)
				free(curr_var->value);
			curr_var->value = NULL;
			curr_var->value = ft_strdup(val);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

char	**lst_to_arr(t_mshell *shell)
{
	int			i;
	char		**envp;
	t_envvar	*var;
	t_list		*temp;
	char		*str_tmp;

	envp = malloc(sizeof(char *) * ft_lstsize(shell->env_copy));
	if (!envp)
		error_exit(NULL);
	temp = shell->env_copy;
	i = 0;
	while (temp)
	{
		var = (t_envvar *)(temp->content);
		str_tmp = ft_strjoin(var->key, "=");
		if (!str_tmp)
			error_exit(NULL);
		envp[i] = ft_strjoin(str_tmp, var->value);
		if (!envp[i])
			error_exit(NULL);
		free(str_tmp);
		temp = temp->next;
		i++;
	}
	return (envp);
}

void	add_var(t_mshell *shell, char *key, char *val)
{ /* var with name '_' always goes last */
	t_list		*last_node;
	t_list		*node_before_last;
	t_list		*new_node;
	t_envvar	*new_var;

	last_node = get_by_key(shell, "_");
	node_before_last = shell->env_copy;
	while (node_before_last->next != last_node)
		node_before_last = node_before_last->next;
	new_var = malloc(sizeof(t_envvar));
	if (!new_var)
		error_exit(NULL);
	*new_var = (t_envvar){.key = ft_strdup(key), .value = ft_strdup(val)};
	new_node = ft_lstnew(new_var);
	node_before_last->next = new_node;
	new_node->next = last_node;
}
