/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c     		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:10:54 by namina             #+#    #+#            */
/*   Updated: 2021/09/10 19:10:54 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_path(char *cmd_name)
{
	while (*cmd_name == '.')
		cmd_name++;
	if (*cmd_name == '/')
		return (1);
	return (0);
}

/* TODO
 * check program (stat?) DONE, the executable rights will be checked in execve
 * check redirects
 *
 * */
void	check_status_path(t_list *params)
{
	t_list_params	*param;

	param = (t_list_params *)(params->content);
	if (!param->path_app)
	{
		if (!(is_path(param->cmd_arr[0])))
			print_err_msg(NULL, param->cmd_arr[0], "command not found");
		free_arr(param->cmd_arr); //maybe not because it will be cleared
		// altogether
		param->cmd_arr = NULL;
	}
}

void	assign_path(t_list_params *el, struct stat *buf)
{
	int	err;

	err = stat(el->cmd_arr[0], buf);
	if (err == -1)
	{
		print_error(NULL, el->cmd_arr[0]);
		return ;
	}
	el->path_app = el->cmd_arr[0];
	free(buf);
}

void	check_access(char **path, t_list_params *el)
{
	char			**path_pointer;
	struct stat		*buf;
	int				err;

	path_pointer = path;
	buf = malloc(sizeof(struct stat));
	if (is_path(el->cmd_arr[0]))
	{
		assign_path(el, buf);
		return ;
	}
	while (path && *path_pointer)
	{
		err = stat(*path_pointer, buf);
		if (err != -1)
		{
			el->path_app = ft_strdup(*path_pointer);
			break ;
		}
		path_pointer++;
	}
	free_arr(path);
	free(buf);
}

int	validation(t_list *param_list, char **envp)
{
	char			**path;
	t_list_params	*el;

	while (param_list)
	{
		el = (t_list_params *)param_list->content;
		if (!el->cmd_arr || !el->cmd_arr[0])
		{
			param_list = param_list->next;
			continue ;
		}
		assign_func(el);
		if (el->builtin)
		{
			param_list = param_list->next;
			continue ;
		}
		path = get_path_arr(envp, el->cmd_arr[0]);
		check_access(path, el);
		check_status_path(param_list);
		param_list = param_list->next;
	}
	return (0);
}

//int	validation(t_list *param_list, char **envp)
//{
//	if (!param_list)
//	{printf("param list is empty\n"); return (-1);}
//	check_apps(param_list, envp);
//	return (0);
//}

/*int	main(int argc, char **argv, char **envp)
{
	struct stat		*buf;

	char *argvs[] = {"./valid", NULL};
	buf = malloc(sizeof(struct stat));
	int i = stat("./valid", buf);
	printf("%d - status code, %d - errno\n", i, errno);
	perror("");
	int j = execve("../valid", argvs, envp);
	printf("%d - status code, %d - errno\n", j, errno);
	perror("");
	return (0);
}*/
