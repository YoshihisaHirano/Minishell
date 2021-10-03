/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:23:15 by namina            #+#    #+#             */
/*   Updated: 2021/08/09 22:23:17 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free_array(tmp->cmd_arr);
		free(tmp->path_app);
		free(tmp);
		tmp = next;
	}
	*lst = 0;
}
