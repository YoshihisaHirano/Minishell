/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                          :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:35:48 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/13 13:35:48 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	deal_with_spaces(char **start, char **str, char **res)
{
	char	*res_w_space;

	if (ft_isspace(**str))
	{
		res_w_space = ft_strjoin(*res, " ");
		free(*res);
		*res = res_w_space;
	}
	move_spaces(str, start);
}

void	update_var_len(char *var, size_t *var_len)
{
	while (*var && !ft_isspace(*var) && *var != '\'' && *var != '\"'
		   && *var!='$')
	{
		(*var_len)++;
		var++;
	}
}

char	*change_to_expanded(char **var, t_mshell *shell)
{
	size_t	var_len;
	t_list	*node;
	char	*temp;
	char	*copy;

	var_len = 1;
	copy = *var;
	while (*copy != '$')
		copy++;
	copy++;
	if (*copy == '?')
		return (ft_itoa(shell->last_exit_code));
	update_var_len(copy, &var_len);
	if (var_len == 1)
		return (ft_strdup("$"));
	temp = ft_substr(copy, 0, var_len - 1);
	node = get_by_key(shell, temp);
	free(temp);
	*var += var_len;
	if (!node)
		return (ft_strdup(""));
	return (((t_envvar *)(node->content))->value);
}

char	*add_expanded(char **start, char **str, char *res, t_mshell *shell)
{
	int		dst;
	char	*tmp;
	char	*tmp2;
	char	*expanded;
	char	*new_res;

	dst = *str - *start;
	tmp = NULL;
	if (dst > 0)
		tmp = ft_substr(*start, 0, dst);
	expanded = change_to_expanded(str, shell);
	if (tmp)
	{
		tmp2 = ft_strjoin(res, tmp);
		free(tmp);
		new_res = ft_strjoin(tmp2, expanded);
		free(tmp2);
	}
	else
		new_res = ft_strjoin(res, expanded);
	if (*res)
		free(res);
	free(expanded);
	deal_with_spaces(start, str, &new_res);
	return (new_res);
}