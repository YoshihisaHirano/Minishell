/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_manager(t_list_params *element)
{
	if (element->path_app && element->path_app[0])
		element->pid = fork();
	if (element->pid == -1)
	{
		perror("Minishell: fork");
		return (-1);
	}
	return (0);
}

void	close_pipes_parent(void *params)
{
	t_list_params	*element;

	element = (t_list_params *) params;
	close(element->pipe_fd[0]);
	element->pipe_fd[0] = -1;
}

int	pipe_error_handler(char *app_name)
{
	perror(app_name);
	return (-1);
}
