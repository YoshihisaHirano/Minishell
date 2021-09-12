/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:00:58 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/09 16:00:58 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
oa-d3% echo '$HOME'
 $HOME
oa-d3% echo $'HOME'
 HOME
oa-d3% echo $HOME
 /Users/aalannys
oa-d3% echo '$HO'ME
 $HOME
oa-d3% echo HO'$'HOME
 HO$HOME
 if there are two quotes before and after $ sign (no matter in what part of the
 word), the whole word is taken literary, with no expansion
 */

/*
oa-d3% echo 'HELLOO$H'OME
	HELLOO$HOME
 */
int	single_quotes(char *var)
{
	int res;

	res = 0;
	while (*var)
	{
		if (*var == '\'' && *(var + 1) == '$') //it might not be consecutive !!!
		{
			res++;
			var++;
			break ;
		}
		var++;
	}
	while (*var)
	{
		if (*var == '\'')
		{
			res++;
			break;
		}
		var++;
	}
	if (res == 2)
		return (1);
	return (0);
}

char	*compose_str(char *start, char *val)
{
	char	*temp;
	size_t	size;
	char	*res;

	size = 0;
	while (*start != '$')
	{
		size++;
		start++;
	}
	temp = ft_substr(start - size, 0, size);
	res = ft_strjoin(temp, val);
	free(temp);
	return (res);
}

char	*remove_quotes(char *var)
{
	char	*start;
	char	*temp1;
	char	*temp2;
	size_t	size;
	char	*res;

	start = var;
	size = 0;
	while (*var++ != '\'')
		size++;
	temp1 = ft_substr(start, 0, size);
	temp2 = ft_substr(var, 0, ft_strlen(var));
	res = ft_strjoin(temp1, temp2);
	free(start);
	free(temp1);
	free(temp2);
	return (res);
}

char	*expand_var(char *var, t_mshell *shell) // it might not start from $ !!!
{
	char	*res;
	t_list	*node;
	char	*start;

	start = var;
	if (single_quotes(var))
		return (remove_quotes(var));
	while (*var != '$')
		var++;
	var++;
	if (*var == '?')
	{
		res = compose_str(start, ft_itoa(shell->last_exit_code));
		free(start);
		return (res);
	}
	node = get_by_key(shell, var);
	if (!node)
		res = ft_strdup("");
	else
		res = compose_str(start, ((t_envvar *)(node->content))->value);
	free(start);
	return (res);
}