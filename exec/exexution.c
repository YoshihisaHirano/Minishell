/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_list_params
{
	char	**cmd_arr;
	char	*str_to_cmd;
	char	*path_app;
	int		fd[2];
	char	*here_doc_limiter;
	int		input_mod;
	int 	output_mode;
	char 	*input_file;
	int		fd_output;
	char 	*output_file;
}			t_list_params;

void	child_process(t_list *params, int input_fd, int last_output_fd,
					   char **envp)
{
	t_list	*tmp;

	tmp = params;
	set_child_fd(params, input_fd, last_output_fd);
	execve(params->path_app, params->cmd_arr, envp);
	while (tmp->prev)
		tmp = tmp->prev;
	ft_lstclear(&tmp);
	exit(-1);
}

int	my_exec(t_list *params, int input_fd, int last_output_fd, char **envp)
{
	int		pid;
	int		fds[2];

	pipe(params->fd);
	if (params->limiter)
	{
		pipe(fds);
		get_input_from_std(params->limiter, fds[1]);
		close(fds[1]);
		input_fd = fds[0];
	}
	pid = fork();
	if (pid == 0)
		child_process(params, input_fd, last_output_fd, envp);
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(params->fd[1]);
		if (input_fd > 0)
			close(input_fd);
		if (!params->next)
			close(params->fd[0]);
	}
	return (params->fd[0]);
}

int set_input_output(t_list_params *params, int *input_fd)
{
	if (params->limiter)
		params->fd_output = open(params->output_file, O_WRONLY | O_CREAT |
		O_APPEND, 0777);
	else if (params->output_file)
		params->fd_output = open(params->output_file, O_WRONLY | O_TRUNC |
		O_CREAT, 0777);
	if (params->fd_output == -1)
		perror(output_file);
	if (params->limiter)
		*input_fd = -1;
	else
	{
		input_fd = open(input_file, O_RDONLY);
		if (*input_fd == -1)
			perror(input_file);
	}
}

void	exec_manager(t_list *params, char **envp)
{
	t_list_params	*element;
	int 			input_fd;

	while (params)
	{
		element = (t_list_params *) params->content;
		set_input_output(element, &input_fd);
		if (params->cmd_arr)
			input_fd = my_exec(params, &input_fd, last_output_fd, envp);
		else
		{
			if (input_fd != -1)
			{
				close(input_fd);
				input_fd = -1;
			}
		}
		params = params->next;
	}
	if (last_output_fd != -1)
		close(last_output_fd);
}

int	execution(t_list *param_list, char **envp)
{
//	set_files_and_exec(param_list, envp);
	exec_manager(params, envp);
//	ft_lstclear(&param_list);
	return (0);
}
