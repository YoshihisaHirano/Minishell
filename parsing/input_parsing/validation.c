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

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
//# include "readline/include/readline/readline.h"
//# include "readline/include/readline/history.h"
//# include "readline/include/readline/rltypedefs.h"
# include "../../minishell.h"

#define PIPE 1
#define REDRCT_OUTPUT 2
#define REDRCT_APPEND 3
#define REDRCT_INPUT 4
#define HERE_DOC 5
#define CHECK_EXE_ACCESS(x) (((x << 9) >> 15) & 0001) == 0001


char	**get_path_arr(char **envp, char *app_name);

/* TODO
 * check program (stat?)
 * check redirects
 *
 * */
void	free_array(char **arr)
{
	char	**p;

	p = arr;
	if (!arr)
		return ;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(p);
}

void	check_status_path(t_list *params, char **path)
{
	free_array(path);
	if (((t_list_params *)(params->content))->path_app)
	{
		printf("app is ok\n%s\n", ((t_list_params *)(params->content))->path_app);
	}
	else
	{
		printf("app isnt work\n");
//		error_handle_program(((t_list_params *)params)->cmd_arr[0]);
//		free_array(((t_list_params *)params)->cmd_arr);
//		((t_list_params *)params)->cmd_arr = NULL;
	}
}

void check_access(char **path, t_list_params *el)
{
	char			**path_pointer;
	struct stat		*buf;

	path_pointer = path;
	buf = malloc(sizeof(struct stat));
	while (path && *path_pointer)
	{
		stat(*path_pointer, buf);
		if (CHECK_EXE_ACCESS(buf->st_mode))
		{
			el->path_app = ft_strdup(*path_pointer);
			free(buf);
			return ;
		}
		path_pointer++;
	}
	free(buf);
}

int	check_apps(t_list *param_list, char **envp)
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
		path = get_path_arr(envp, el->cmd_arr[0]);
		check_access(path, el);
		check_status_path(param_list, path);
		param_list = param_list->next;
	}
	return (0);
}

int	validation(t_list *param_list, char ** envp)
{
	if (!param_list)
	{printf("param list is empty\n"); return (-1);}
	check_apps(param_list, envp);
	return (0);
}
