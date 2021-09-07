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

void	error_exit(char *prog)
{
	if (!prog)
		perror("Minishell");
	else
	{
		printf("Minishell: ");
		perror(prog);
	}
	exit(errno);
}

void	print_node(void *node)
{
	t_envvar	*var;

	var = (t_envvar *)node;
	printf("%s=%s\n", var->key, var->value);
}

void	free_arr(char **arr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
