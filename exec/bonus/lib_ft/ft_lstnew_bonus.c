/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:23:53 by namina            #+#    #+#             */
/*   Updated: 2021/08/09 22:23:55 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

t_list	*ft_lstnew(char **cmd_arr)
{
	t_list	*new;

	new = malloc(sizeof (t_list));
	if (!new)
		return (0);
	new->next = 0;
	new->cmd_arr = cmd_arr;
	new->path_app = NULL;
	new->prev = 0;
	new->limiter = NULL;
	return (new);
}
