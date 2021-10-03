/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:24:47 by namina            #+#    #+#             */
/*   Updated: 2021/08/09 22:24:48 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static	int	count_words(char *str, char c)
{
	int		words;

	words = 0;
	while (*str)
	{
		while (*str == c && *str)
		{
			*str = '\0';
			str++;
		}
		if (*str)
		{
			words++;
			while (*str != c && *str)
				str++;
		}
	}
	return (words);
}

static void	cleararr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
}

static char	**fillarr(char *str, char **arr, int words, size_t len)
{
	int		i;

	i = 0;
	while (i < words)
	{
		while (!*str && len--)
			str++;
		arr[i] = ft_strdup(str);
		if (!arr[i])
		{
			free(str);
			cleararr(arr, i - 1);
			return (NULL);
		}
		while (*str && len--)
			str++;
		i++;
	}
	arr[words] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	*str;
	char	**arr;
	size_t	len;

	if (!s)
		return (NULL);
	str = ft_strdup((char *) s);
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	words = count_words(str, c);
	arr = (char **) malloc((words + 1) * sizeof(str));
	if (!arr)
		return (NULL);
	if (!fillarr(str, arr, words, len))
		return (NULL);
	free(str);
	return (arr);
}
