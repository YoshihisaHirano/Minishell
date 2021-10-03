/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:13:04 by namina             #+#    #+#            */
/*   Updated: 2021/08/14 13:13:04 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

#define PATH "PATH="

char	*get_path(char *absolute_path, char *app_name)
{
	char	*path;
	char	*path_pointer;

	path = ft_calloc(ft_strlen(absolute_path) + ft_strlen(app_name) + 2, 1);
	path_pointer = path;
	if (!path)
		exit(-1);
	while (*absolute_path)
	{
		*path_pointer = *absolute_path;
		path_pointer++;
		absolute_path++;
	}
	*path_pointer = '/';
	path_pointer++;
	while (*app_name)
	{
		*path_pointer = *app_name;
		path_pointer++;
		app_name++;
	}
	*path_pointer = '\0';
	return (path);
}

void	set_path_arr(char **current_path_arr, char *app_name)
{
	char	**path_arr;
	char	*prev_path;

	path_arr = current_path_arr;
	while (*path_arr)
	{
		prev_path = *path_arr;
		*path_arr = get_path(prev_path, app_name);
		free(prev_path);
		path_arr++;
	}
}

char	**get_path_arr(char **envp, char *app_name)
{
	char	**en;
	char	**path_arr;

	en = envp;
	path_arr = NULL;
	while (en && *en)
	{
		if (ft_strnstr(*en, PATH, 5))
		{
			path_arr = ft_split((*en) + 5, ':');
			break ;
		}
		en++;
	}
	if (!path_arr)
		return (NULL);
	set_path_arr(path_arr, app_name);
	return (path_arr);
}

void	parser(t_list **param_list, char **argv, char **input_file,
			   char **output_file)
{
	int		i;
	char	*limiter;

	limiter = NULL;
	i = 1;
	if (!ft_strncmp(argv[i], "here_doc\0", 9))
	{
		limiter = argv[++i];
		i++;
	}
	else
		*input_file = argv[i++];
	while (argv[i])
	{
		if (argv[i + 1] == NULL)
		{
			*output_file = argv[i];
			break ;
		}
		ft_lstadd_back(param_list,
			ft_lstnew(ft_split(argv[i++], ' ')));
	}
	if (limiter)
		(*param_list)->limiter = limiter;
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
