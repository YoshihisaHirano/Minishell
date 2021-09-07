/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:42:41 by aalannys            #+#   #+#            */
/*   Updated: 2021/09/07 15:42:41 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(void)
{
	perror("Minishell");
	exit(errno);
}

void	*free_node(void *node)
{
	free(node);
	return (NULL);
}

void	*print_node(void *node)
{
	t_envvar	*var;

	var = (t_envvar)node;
	printf("%s=%s\n", var->key, var->value);
	return (NULL);
}