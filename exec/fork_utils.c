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

int	check_exec_access(t_list_params *element)
{
	struct stat buf;

	stat(element->path_app, &buf);
	if ((((buf.st_mode << 9) >> 15) & 0001) == 0001)
		return (0);
	else
	{
		print_err_msg(NULL, element->path_app, "permission denied");
		g_last_exit_code = 126;
		return (1);
	}
}

int	fork_manager(t_list_params *element)
{
	if (element->path_app && element->path_app[0])
	{
		if (!check_exec_access(element))
			element->pid = fork();
	}
	else
		g_last_exit_code = 127;
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
	close(element->pipe_fd[1]);
	close(element->pipe_fd[0]);
}