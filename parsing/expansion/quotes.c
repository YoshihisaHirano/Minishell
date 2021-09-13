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

char	*remove_quotes(char *pre_res)
{
	(void)pre_res;
	return (NULL);
}