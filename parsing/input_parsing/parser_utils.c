/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:27:23 by namina             #+#    #+#            */
/*   Updated: 2021/10/07 22:27:23 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char	*ft_chr_check(const char *s, int c)
{
	char	*chr;
	char	sym;

	sym = (char)c;
	chr = (char *)s;
	if (sym == '\0')
		return (chr);
	while (*chr)
	{
		if (*chr == sym)
			return (chr);
		chr++;
	}
	return (NULL);
}

int get_io_name(char **param_to_set, char **s)
{
	int size;
	int double_quotes;
	int single_quotes;

	size = 0;
	double_quotes = 0;
	single_quotes = 0;
	while ((*s)[size]) {
		if ((*s)[size] == '\"' && !(single_quotes % 2))
			double_quotes++;
		if ((*s)[size] == '\'' && !(double_quotes % 2))
			single_quotes++;
		if (ft_chr_check(" \r\f\t\v\n><|", (*s)[size]) &&
			!(double_quotes % 2) && !(single_quotes % 2))
			break;
		size++;
	}
	*param_to_set = ft_substr((*s), 0, size);
	(*s) += size;
	return (0);
}

void handle_quotes(char **s, t_list_params *el, int *i)
{
	int double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	while (**s)
	{
		if (**s == '\"' && !(single_quotes % 2))
			double_quotes++;
		if (**s == '\'' && !(double_quotes % 2))
			single_quotes++;
		el->str_to_cmd[*i] = **s;
		(*i)++;
		(*s)++;
		if (!(double_quotes % 2) && !(single_quotes % 2))
			break;
	}
}

int	handle_token_error(char **input_str, char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 1);
	while(**input_str == token)
	{
		ft_putchar_fd(token, 1);
		(*input_str)++;
	}
	ft_putstr_fd("\'\n", 1);
	return (-1);
}
