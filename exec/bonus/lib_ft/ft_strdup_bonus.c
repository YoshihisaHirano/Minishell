/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:24:54 by namina            #+#    #+#             */
/*   Updated: 2021/08/09 22:24:56 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static char	*ft_strcpy(char *dest, char *src)
{
	char	*p_dest;
	char	*p_src;

	p_dest = dest;
	p_src = src;
	while (*p_src)
	{
		*p_dest = *p_src;
		p_dest++;
		p_src++;
	}
	*p_dest = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	size_t		len;
	char		*p_str;

	len = ft_strlen(src);
	p_str = (char *) malloc(len + 1);
	if (!p_str)
		return (0);
	ft_strcpy(p_str, src);
	return (p_str);
}
