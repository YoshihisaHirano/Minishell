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

int	get_io_name(char **param_to_set, char **s)
{
	int	size;
	int	double_quotes;
	int	single_quotes;

	size = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (ft_isspace(**s))
		(*s)++;
	while ((*s)[size])
	{
		if ((*s)[size] == '\"' && !(single_quotes % 2))
			double_quotes++;
		if ((*s)[size] == '\'' && !(double_quotes % 2))
			single_quotes++;
		if (ft_chr_check(" \r\f\t\v\n><|", (*s)[size]) &&
				!(double_quotes % 2) && !(single_quotes % 2))
			break ;
		size++;
	}
	*param_to_set = ft_substr((*s), 0, size);
	if (check_quotes(*param_to_set) == -1)
		return (-1);
	(*s) += size;
	return (0);
}

void	handle_quotes(char **s, t_list_params *el)
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
		el->str_to_cmd[el->cmd_str_i] = **s;
		el->cmd_str_i++;
		(*s)++;
		if (!(double_quotes % 2) && !(single_quotes % 2))
			break;
	}
}

int	handle_token_error(char **input_str, char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 1);
	if (!token)
	{
		ft_putstr_fd("newline", 1);
		ft_putstr_fd("\'\n", 1);
		return (-1);
	}
	while (**input_str == token)
	{
		ft_putchar_fd(token, 1);
		(*input_str)++;
	}
	ft_putstr_fd("\'\n", 1);
	return (-1);
}

void	process_io_tokens(char **param_to_set, t_mshell *shell, int mode)
{
	char	*preprocessed;

	if (mode == HERE_DOC)
	{
		// some problem here!
		// : pointer being freed was not allocated
		preprocessed = remove_quotes(*param_to_set);
		free(*param_to_set);
		*param_to_set = preprocessed;
	}
	else
	{
		preprocessed = preprocessor(*param_to_set, shell);
		free(*param_to_set);
		*param_to_set = remove_quotes(preprocessed);
	}
	printf("CHECK\n");
}

int check_for_cmd(char *cmd_str)
{
	while (ft_isspace(*cmd_str))
		cmd_str++;
	if (!(*cmd_str))
		return (-1);
	return (0);
}