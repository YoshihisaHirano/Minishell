/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:25:17 by namina            #+#    #+#             */
/*   Updated: 2021/08/09 22:25:18 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	if (!haystack[i])
		return (NULL);
	needle_len = ft_strlen((char *) needle);
	while (len >= needle_len && haystack[i])
	{
		if (haystack[i] == needle[0])
			if (!ft_strncmp(haystack + i, needle, needle_len))
				return ((char *)haystack + i);
		i++;
		len--;
	}
	return (NULL);
}
