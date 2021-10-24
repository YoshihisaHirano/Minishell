/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 18:59:40 by namina             #+#    #+#            */
/*   Updated: 2021/10/23 18:59:40 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_token_error(char **input_str, char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	if (!token)
	{
		ft_putstr_fd("newline", 2);
		ft_putstr_fd("\'\n", 2);
		return (-1);
	}
	while (**input_str == token)
	{
		ft_putchar_fd(token, 2);
		(*input_str)++;
	}
	ft_putstr_fd("\'\n", 2);
	return (-1);
}

int	check_for_pipe_error(char **input_str)
{
	char	*ptr;

	(*input_str)++;
	ptr = *input_str;
	while (ft_isspace(*ptr) && *ptr)
		ptr++;
	if (*ptr == '\0')
	{
		ft_putstr_fd("minishell: syntax error: multiline pipe\n", 2);
		return (-1);
	}
	else if (*ptr == '|')
	{
		handle_token_error(&ptr, '|');
		return (-1);
	}
	return (PIPE);
}