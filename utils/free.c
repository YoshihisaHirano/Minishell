/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:06:31 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/08 21:06:31 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(void *node)
{
	t_envvar	*content;

	content = (t_envvar *)(node);
	free(content->key);
	free(content->value);
	free(content);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_io_params(void *param_node)
{
	t_list_io_params	*content;

	content = (t_list_io_params *)param_node;
	if (content->file_name)
		free(content->file_name);
}

void	free_params_lst(void *param_node)
{
	t_list_params	*content;

	content = (t_list_params *)param_node;
	free_arr(content->cmd_arr);
	free(content->str_to_cmd);
	free(content->path_app);
	if (content->input)
		free_io_params(content->input);
	if (content->output)
		free_io_params(content->output);
	free(content);
}

void	free_builtins(void *content)
{
	t_builtins	*bn;

	bn = (t_builtins *)content;
	free(bn->name);
	free(bn);
}
