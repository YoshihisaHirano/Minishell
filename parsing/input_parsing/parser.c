/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:10:54 by namina             #+#    #+#            */
/*   Updated: 2021/09/10 19:10:54 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
//# include "readline/include/readline/readline.h"
//# include "readline/include/readline/history.h"
//# include "readline/include/readline/rltypedefs.h"
# include "../../libft/libft.h"
# include "../../minishell.h"

#define PIPE 1
#define REDRCT_OUTPUT 2
#define REDRCT_APPEND 3
#define REDRCT_INPUT 4
#define HERE_DOC 5

int	validation(t_list *param_list, char **envp);

void show_params(t_list *list)
{
	t_list_params *param_el;
	t_list *tmp;
	char *modes[] = {"none", "PIPE", "REDRCT_OUTPUT", "REDRCT_APPEND",
					 "REDRCT_INPUT", "HERE_DOC"};
	tmp = list;
	printf("--------------------------\n");
	printf("▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼\n");
	while(tmp)
	{
		printf("--------------------------\n");
		param_el = ((t_list_params *) tmp->content);
		if (param_el->path_app)
			printf("path_app: %s\n", param_el->path_app);
		if (param_el->cmd_arr)
		{
			char **arr = param_el->cmd_arr;
			printf("cdm_arr:\n");
			while(*arr)
			{
				printf("---> |%s|\n", *arr);
				arr++;
			}
		}
		if (param_el->str_to_cmd)
			printf("str_to_cmd: |%s|\n", param_el->str_to_cmd);
		if (param_el->here_doc_limiter)
			printf("here_doc_limiter: |%s|\n", param_el->here_doc_limiter);
		printf("input_mod: %s\noutput_mode: %s\n", modes[param_el->input_mod],
			   modes[param_el->output_mode]);
		if (param_el->input_file)
			printf("input_file: |%s|\n", param_el->input_file);
		if (param_el->output_file)
			printf("output_file: |%s|\n", param_el->output_file);
		tmp = tmp->next;
	}
}

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

t_list_params	*create_empty_el(void)
{
	t_list_params	*el;

	el = malloc(sizeof(t_list_params));
	el->input_mod = 0;
	el->output_mode = 0;
	el->here_doc_limiter = NULL;
	el->path_app = NULL;
	el->cmd_arr = NULL;
	el->input_file = NULL;
	el->output_file = NULL;
	el->fd_output = -1;
	return (el);
}

int get_io_name(char **param_to_set, char **s)
{
	int 	size;
	int		double_quotes;
	int		single_quotes;

	size = 0;
	double_quotes = 0;
	single_quotes = 0;
	while ((*s)[size])
	{
		if ((*s)[size] == '\"')
			double_quotes++;
		if ((*s)[size] == '\'')
			single_quotes++;
		if (ft_chr_check(" \r\f\t\v\n><|", (*s)[size]) &&
			!(double_quotes % 2) && !(single_quotes % 2))
				break ;
		size++;
	}
	*param_to_set = ft_substr((*s), 0, size);
	(*s) += size;
	return (0);
}

int	set_input_mode(char **input_str, t_list_params *params_el)
{
	char	**param_to_set;

	if (params_el->input_mod)
		return (-1);
	if (!ft_strncmp(*input_str, "<<", 2))
	{
		param_to_set = &(params_el->here_doc_limiter);
		(*input_str) += 2;
		params_el->input_mod = HERE_DOC;
	}
	else
	{
		param_to_set = &(params_el->input_file);
		(*input_str)++;
		params_el->input_mod = REDRCT_INPUT;
	}
	while (ft_isspace(**input_str))
		(*input_str)++;
	get_io_name(param_to_set, input_str);
	return (0);
}

int	set_output_mode(char **input_str, t_list_params *params_el)
{
	if (params_el->output_mode)
		return (-1);
	if (**input_str == '|')
	{
		params_el->output_mode = PIPE;
		(*input_str)++;
		return (0);
	}
	else if (!ft_strncmp(*input_str, ">>", 2))
		params_el->output_mode = REDRCT_APPEND;
	else
		params_el->output_mode = REDRCT_OUTPUT;
	if (params_el->output_mode == REDRCT_APPEND)
		(*input_str) += 2;
	else
		(*input_str)++;
	while (ft_isspace(**input_str))
		(*input_str)++;
	get_io_name(&(params_el->output_file), input_str);
	return (0);
}

int	set_params_to_el(char **input_str, t_list_params *el)
{
	int		i;
	int		res;

	i = 0;
	el->str_to_cmd = malloc(ft_strlen(*input_str) + 1);
	while (**input_str)
	{
		if (**input_str == '<')
			res = set_input_mode(input_str, el);
		else if (**input_str == '|' || **input_str == '>')
			res = set_output_mode(input_str, el);
		else
		{
			el->str_to_cmd[i++] = **input_str;
			if (**input_str)
				(*input_str)++;
		}
		if (el->output_mode == PIPE)
			break ;
		if (res == -1)
			return (res);
	}
	el->str_to_cmd[i] = '\0';
	return (0);
}

int	parser(char *input_str, t_list **list)
{
	t_list_params	*el;

	while (*input_str)
	{
		el = create_empty_el();
		if (set_params_to_el(&input_str, el))
		{
			printf("Okay, Houston...we've had a problem here\n");
			// get out
		}
		ft_lstadd_back(list, ft_lstnew(el));
	}
	return (0);
}

/*TODO extra > or < pr | ??*/

int	main(int argc, char **argv, char **envp)
{
	t_list			*list;
////////
	argc++;
	argv++;
////////
//	char *s = "grep<lol\tnew<new.txt";
//	char *s = "\"cat -e\">out";
	char *s = "bash | out";
	list = NULL;
	parser(s, &list);
	validation(list, envp);
	show_params(list);
	return (0);
}