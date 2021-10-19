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
/*TODO cat | rev ??  */

/*TODO SOMETHING WRONG WITH SET FDS. CAT | REV */

void	set_child_fd(t_list *params, int file_fd[], int pipe_fd[])
{
	if (!((t_list_params *) params->content)->builtin)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (file_fd[0] > 0)
		dup2(file_fd[0], STDIN_FILENO);
//	else if (file_fd[0] == -2)
//		dup2(pipe_fd[0], STDIN_FILENO);
	if (file_fd[1] > 0)
	{
		dup2(file_fd[1], STDOUT_FILENO);
		if (!((t_list_params *) params->content)->builtin)
		{
			close(pipe_fd[1]);
			pipe_fd[1] = -1;
		}
	}
	else if (file_fd[1] == -2 || file_fd[1] == PIPE_FD)
		dup2(pipe_fd[1], STDOUT_FILENO);
}

void	set_parrent_fd(t_list *params, int file_fd[], int pipe_fd[])
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipe_fd[1] = -1;
	if (file_fd[0] > 0)
	{
		close(file_fd[0]);
		file_fd[0] = -1;
	}
	if (!params->next)
		close(pipe_fd[0]);
}

int	builtin_exec(t_list *params, int file_fd[], int pipe_fd[], t_mshell *shell)
{
	int				stdout_copy;
	int				stdin_copy;
	t_list_params	*element;

	element = (t_list_params *) params->content;
	stdout_copy = dup(STDOUT_FILENO);
	stdin_copy = dup(STDIN_FILENO);
	set_child_fd(params, file_fd, pipe_fd);
	element->builtin(shell, element);
	set_parrent_fd(params, file_fd, pipe_fd);
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	return (pipe_fd[0]);
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

int	app_to_null(t_list_params *params, int check_pipe)
{
	if (check_pipe == PIPE_FD)
		ft_putstr_fd("syntax error: multiline pipe\n", 2);
	if (params->path_app)
		free(params->path_app);
	params->path_app = NULL;
	params->builtin = NULL;
	return (-1);
}
