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

#include "pipex_bonus.h"

int	error_handle_program(char *app_name)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(app_name, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

void	set_child_fd(t_list *params, int input_fd, int last_output_fd)
{
	if (input_fd > 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(params->fd[0]);
	}
	else
		dup2(params->fd[0], STDIN_FILENO);

	if (!params->next)
	{
		if (last_output_fd > 0)
		{
			dup2(last_output_fd, STDOUT_FILENO);
			close(params->fd[1]);
		}
		else
			dup2(params->fd[1], STDOUT_FILENO);
	}
	else
		dup2(params->fd[1], STDOUT_FILENO);
}

void	check_status_path(int check_status, t_list *params, char **path)
{
	free_array(path);
	if (check_status == -1)
	{
		error_handle_program(params->cmd_arr[0]);
		free_array(params->cmd_arr);
		params->cmd_arr = NULL;
	}
}

int	validation(char *input_file, t_list *param_list, int argc, char **envp)
{
	char	**path;
	char	**path_pointer;
	int		check_stat;

	check_stat = -1;
	if (!param_list || (!input_file && argc < 6))
		return (-1);
	while (param_list)
	{
		path = get_path_arr(envp, param_list->cmd_arr[0]);
		path_pointer = path;
		while (path && *path_pointer)
		{
			check_stat = access(*path_pointer, X_OK);
			if (check_stat == 0)
			{
				param_list->path_app = ft_strdup(*path_pointer);
				break ;
			}
			path_pointer++;
		}
		check_status_path(check_stat, param_list, path);
		param_list = param_list->next;
	}
	return (0);
}

int	error_handle_argc(void)
{
	ft_putstr_fd("------------------------------\n", 2);
	ft_putstr_fd("Need at least 4 args:\n", 2);
	ft_putstr_fd("file1 cmd1 ... cmdn file2\n", 2);
	ft_putstr_fd("For here_doc at least 5 args:\n", 2);
	ft_putstr_fd("here_doc LIMITER cmd cmd1 file\n", 2);
	ft_putstr_fd("------------------------------\n", 2);
	return (-1);
}
