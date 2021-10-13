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
//
//int	error_handle_program(char *app_name)
//{
//	ft_putstr_fd("command not found: ", 2);
//	ft_putstr_fd(app_name, 2);
//	ft_putstr_fd("\n", 2);
//	return (-1);
//}
//
//void	set_child_fd(t_list *params, int input_fd, int last_output_fd)
//{
//	if (input_fd > 0)
//	{
//		dup2(input_fd, STDIN_FILENO);
//		close(params->fd[0]);
//	}
//	else
//		dup2(params->fd[0], STDIN_FILENO);
//
//	if (!params->next)
//	{
//		if (last_output_fd > 0)
//		{
//			dup2(last_output_fd, STDOUT_FILENO);
//			close(params->fd[1]);
//		}
//		else
//			dup2(params->fd[1], STDOUT_FILENO);
//	}
//	else
//		dup2(params->fd[1], STDOUT_FILENO);
//}
//
//void	check_status_path(int check_status, t_list *params, char **path)
//{
//	free_array(path);
//	if (check_status == -1)
//	{
//		error_handle_program(params->cmd_arr[0]);
//		free_array(params->cmd_arr);
//		params->cmd_arr = NULL;
//	}
//}

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
