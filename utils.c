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

void	print_error(char *prog)
{
	if (!prog)
		perror("Minishell");
	else
	{
		write(2, "Minishell: ", 11);
		perror(prog);
	}
}

void	error_exit(char *prog)
{ //on malloc errors the whole program exits: should it be changed?
	print_error(prog);
	exit(errno);
}

void	print_node(void *node)
{
	t_envvar	*var;

	var = (t_envvar *)node;
	printf("%s=%s\n", var->key, var->value);
}

void	free_node(void *node)
{
	t_envvar	*content;
	t_list		*elt;

	elt = (t_list *)node;
	content = (t_envvar *)(elt->content);
	free(content->value);
	free(content->key);
	free(content);
}
