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

int	my_exec(t_list *params, int file_fd[], char **envp)
{
	int				pid;
	int				pipe_fd[2];
	t_list_params	*element;

	element = (t_list_params *) params->content;
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		set_child_fd(params, file_fd, pipe_fd);
		execve(element->path_app, element->cmd_arr, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		if (file_fd[0] > 0)
		{
			close(file_fd[0]);
			file_fd[0] = -1;
		}
		if (!params->next)
			close(pipe_fd[0]);
	}
	return (pipe_fd[0]);
}

int	open_files(t_list_io_params *io_el)
{
	int	fds[2];

	if (io_el->mode == PIPE)
		return (PIPE_FD);
	if (io_el->mode == HERE_DOC)
	{
		pipe(fds);
		get_input_from_std(io_el->file_name, fds[1]);
		close(fds[1]);
		io_el->fd = fds[0];
	}
	if (io_el->mode == REDRCT_INPUT)
		io_el->fd = open(io_el->file_name, O_RDONLY);
	if (io_el->mode == REDRCT_OUTPUT)
		io_el->fd = open(io_el->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (io_el->mode == REDRCT_APPEND)
		io_el->fd = open(io_el->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io_el->fd == -1)
	{
		io_el->fd = -2;
		perror(io_el->file_name);
	}
	return (io_el->fd);
}

int	set_input_output(t_list_params *params, int *io_fd)
{
	t_list	*tmp;

	tmp = params->input;
	while (tmp)
	{
		io_fd[0] = open_files((t_list_io_params *) tmp->content);
		if (io_fd[0] == -1 || io_fd[0] == -2)
			return (app_to_null(params));
		tmp = tmp->next;
	}
	tmp = params->output;
	while (tmp)
	{
		io_fd[1] = open_files((t_list_io_params *) tmp->content);
		if (io_fd[1] == -1 || io_fd[1] == -2)
			return (app_to_null(params));
		tmp = tmp->next;
	}
	return (0);
}

void	exec_manager(t_list *params, char **envp)
{
	t_list_params	*element;
	int				io_fd[2];
	int				last_pipe_read;

	last_pipe_read = -1;
	while (params)
	{
		io_fd[0] = -1;
		io_fd[1] = -1;
		element = (t_list_params *) params->content;
		set_input_output(element, io_fd);
		if (io_fd[0] == -1)
			io_fd[0] = last_pipe_read;
		if (element->path_app && element->path_app[0])
			last_pipe_read = my_exec(params, io_fd, envp);
		else
		{
			if (io_fd[0] != -1)
			{
				close(io_fd[0]);
				io_fd[0] = -1;
			}
		}
		params = params->next;
	}
}

int	execution(char *cmd_str, t_mshell *shell)
{
	t_list			*list;
	char			**envp;
	t_list_params	*cmd;

	envp = lst_to_arr(shell);
	list = NULL;
	if (parser(cmd_str, &list, shell) != -1)
	{
		validation(list, envp);
		exec_manager(list, envp);
//		show_params(list);
		cmd = (t_list_params *)(list->content);
		if (cmd->builtin != NULL)
			cmd->builtin(shell, cmd);
	}
	free_arr(envp);
	ft_lstclear(&list, free_params_lst);
	return (0);
}
