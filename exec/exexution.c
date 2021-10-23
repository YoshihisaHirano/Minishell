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

int	my_exec(t_list *params, char **envp, t_mshell *shell)
{
	t_list_params	*element;

	element = (t_list_params *) params->content;
	pipe(element->pipe_fd);
	if (element->builtin)
		return (builtin_exec(params, shell));
	if (element->path_app && element->path_app[0])
		element->pid = fork();
	else
		g_last_exit_code = 127;
	if (element->pid != 0)
		handle_for_child(element->path_app);
	if (element->pid == 0)
	{
		set_child_fd(params);
		execve(element->path_app, element->cmd_arr, envp);
	}
	close(element->pipe_fd[1]);
	return (element->pipe_fd[0]);
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

int	set_input_output(t_list_params *params, int *io_fd, t_list *list)
{
	t_list	*tmp;
	int		tmp_fd;

	tmp = params->input;
	while (tmp)
	{
		io_fd[0] = open_files((t_list_io_params *) tmp->content);
		if (io_fd[0] == -1 || io_fd[0] == -2)
			return (app_to_null(params, io_fd[0]));
		tmp = tmp->next;
	}
	tmp = params->output;
	while (tmp)
	{
		tmp_fd = open_files((t_list_io_params *) tmp->content);
		if (io_fd[1] == -1 && tmp_fd == PIPE_FD)
			io_fd[1] = PIPE_FD;
		else if (tmp_fd != PIPE_FD)
			io_fd[1] = tmp_fd;
		if (io_fd[1] == -1 || io_fd[1] == -2
			|| (tmp_fd == PIPE_FD && !list->next))
			return (app_to_null(params, io_fd[1]));
		tmp = tmp->next;
	}
	return (0);
}

void	exec_manager(t_list *params, char **envp, t_mshell *shell)
{
	t_list_params	*element;
	int				last_pipe_read;
	t_list			*tmp;

	tmp = params;
	last_pipe_read = -1;
	while (tmp)
	{
		element = (t_list_params *) tmp->content;
		set_input_output(element, element->file_fd, tmp);
		if (element->file_fd[0] == -1)
			element->file_fd[0] = last_pipe_read;
		last_pipe_read = my_exec(tmp, envp, shell);
		tmp = tmp->next;
	}
	parrent_process_handler(params);
}

int	execution(char *cmd_str, t_mshell *shell)
{
	t_list			*list;
	char			**envp;

	envp = lst_to_arr(shell);
	list = NULL;
	if (parser(cmd_str, &list, shell) != -1)
	{
		validation(list, envp);
		exec_manager(list, envp, shell);
	}
	free_arr(envp);
	ft_lstclear(&list, free_params_lst);
	return (0);
}
