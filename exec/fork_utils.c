/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_access(t_list_params *element)
{
	struct stat buf;

	stat(element->path_app, &buf);
	if ((((buf.st_mode << 9) >> 15) & 0001) == 0001)
		return (0);
	else
	{
		print_err_msg(NULL, element->path_app, "permission denied");
		g_last_exit_code = 126;
		return (1);
	}
}