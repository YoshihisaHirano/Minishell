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
	printf("%s=", var->key);
	if (var->value)
		printf("%s", var->value);
	printf("\n");
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

/* Only ASCII letters (of either case), _ and digits are supported, and the
 * first character must not be a digit. */
int	invalid_key(char *key)
{
	if (ft_isdigit(*key))
		return (1);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (1);
		key++;
	}
	return (0);
}
