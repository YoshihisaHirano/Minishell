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

//void	child_process(t_list *params, int input_fd, int last_output_fd,
//					   char **envp)
//{
//	t_list	*tmp;
//
//	tmp = params;
//	set_child_fd(params, input_fd, last_output_fd);
//	execve(params->path_app, params->cmd_arr, envp);
//	while (tmp->prev)
//		tmp = tmp->prev;
//	ft_lstclear(&tmp);
//	exit(-1);
//}
//
//int	my_exec(t_list *params, int io_fd[], char **envp)
//{
//	int		pid;
//	int		fds[2];
//
//	pipe(params->fd);
//	pid = fork();
//	if (pid == 0)
//		child_process(params, input_fd, last_output_fd, envp);
//	else
//	{
//		waitpid(pid, NULL, WNOHANG);
//		close(params->fd[1]);
//		if (input_fd > 0)
//			close(input_fd);
//		if (!params->next)
//			close(params->fd[0]);
//	}
//	return (params->fd[0]);
//}
/*TODO HERE_DOC input --> double free?? */
/*TODO double close fds -> set to -1?*/
int	open_files(t_list_io_params *io_el)
{
	int	fds[2];

	if (io_el->mode == PIPE)
		return (-1);
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
		io_el->fd = open(io_el->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (io_el->mode == REDRCT_APPEND)
		io_el->fd = open(io_el->file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (io_el->fd == -1)
		perror(io_el->file_name);
	return (io_el->fd);
}

int set_input_output(t_list_params *params, int *io_fd)
{
	t_list	*tmp;

	tmp = params->input;
	while (tmp)
	{
		io_fd[0] = open_files((t_list_io_params *) tmp->content);
		tmp = tmp->next;
	}
	tmp = params->output;
	while (tmp)
	{
		io_fd[1] = open_files((t_list_io_params *) tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

void	exec_manager(t_list *params, t_mshell *shell, char **envp)
{
	t_list_params	*element;
	int 			io_fd[2];

	(void) envp;
	(void) shell;
	io_fd[0] = -1;
	io_fd[1] = -1;
	while (params)
	{
		element = (t_list_params *) params->content;
		set_input_output(element, io_fd);
		printf("in fd: %d out: %d\n", io_fd[0], io_fd[1]);
//		if (element->path_app)
//			input_fd = my_exec(element, io_fd, envp);
//		else
//		{
//			if (input_fd != -1)
//			{
//				close(input_fd);
//				input_fd = -1;
//			}
//		}
		params = params->next;
	}
	if (io_fd[1] != -1)
	{
		close(io_fd[1]);
		io_fd[1] = -1;
	}
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
		exec_manager(list, shell, envp);
		show_params(list);
		if (((t_list_params *)(list->content))->builtin != NULL)
			((t_list_params *)(list->content))->builtin(shell, (t_list_params *)(list->content));
	}
	free_arr(envp);
	ft_lstclear(&list, free_params_lst);
	return (0);
}
