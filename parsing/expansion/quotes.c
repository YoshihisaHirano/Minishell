/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:43:17 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/13 13:43:17 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quotes(char *str, t_mshell *shell)
{
	int	squotes_num;
	int dquotes_num;

	squotes_num = 0;
	dquotes_num = 0;
	while (*str)
	{
		if (*str == '\"')
			dquotes_num++;
		if (*str == '\'')
			squotes_num++;
		str++;
	}
	if (squotes_num % 2 || dquotes_num % 2)
	{
		shell->last_exit_code = 1;
		printf("Minishell: parse error: unclosed quote\n");
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *res)
{
	t_quotes	q;
	char		*rm_quotes;
	int			i;
	int			j;

	q = (t_quotes){.doubl = 0, .singl = 0};
	rm_quotes = ft_calloc(ft_strlen(res) + 1, 1);
	i = 0;
	j = 0;
	while (res[i])
	{
		if (res[i] == '\"' && !(q.singl % 2))
			q.doubl++;
		if (res[i] == '\'' && !(q.doubl % 2))
			q.singl++;
		if ((q.doubl % 2 && res[i] == '\'') || (q.singl % 2 && res[i] =='\"')
			|| (res[i] != '\'' && res[i] != '\"'))
		{
			rm_quotes[j] = res[i];
			j++;
		}
		i++;
	}
	return (rm_quotes);
}