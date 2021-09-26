/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:22:04 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/23 18:22:04 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *prog) //on malloc errors the whole program exits: should it be changed?
{
	print_error(prog, NULL, NULL);
	exit(errno);
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

size_t	chr_arr_len(char **arr)
{
	size_t	res;

	res = 0;
	while (*arr)
	{
		res++;
		arr++;
	}
	return (res);
}
