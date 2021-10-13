/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 14:38:56 by namina             #+#    #+#            */
/*   Updated: 2021/08/14 14:38:56 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*TODO add error cases (PIPE file output error app ok - work) */
/*TODO add error cases (file output error app ok - work) */
/*TODO add error cases (if one file falls other dont creates) */
/*TODO add pipe case */

void	set_child_fd(t_list *params, int file_fd[], int pipe_fd[])
{
//	printf("file_fd : %d_%d\n pipe_fd: %d_%d\n", file_fd[0],
//		   file_fd[1], pipe_fd[0], pipe_fd[1]);
	if (file_fd[0] != -1)
	{
		dup2(file_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else
		dup2(pipe_fd[0], STDIN_FILENO);
	if (!params->next)
	{
		if (file_fd[1] != -1)
		{
			dup2(file_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
//		else
//			dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
}

void	get_input_from_std(char *limiter, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(line);
		line = NULL;
	}
	free(line);
}

int	app_to_null(t_list_params *params)
{
	if (params->path_app)
		free(params->path_app);
	params->path_app = NULL;
	params->builtin = NULL;
	return (-1);
}
