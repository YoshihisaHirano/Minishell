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
			printf("here_doc_limiter: %s\n", param_el->here_doc_limiter);
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

int	set_input_mode(char **input_str, t_list_params *params_el)
{
	int 	size_to_copy;
	char	**param_to_set;
	int 	mode;

	size_to_copy = 0;
	if (!ft_strncmp(*input_str, "<<", 2))
	{
		param_to_set = &(params_el->here_doc_limiter);
		(*input_str) += 2;
		mode = HERE_DOC;
	}
	else
	{
		param_to_set = &(params_el->input_file);
		(*input_str)++;
		mode = REDRCT_INPUT;
	}
	while (**input_str == ' ' || **input_str == '\t')
		(*input_str)++;
	while (!ft_chr_check(" \t><|", (*input_str)[size_to_copy]))
		size_to_copy++;
	*param_to_set = ft_strtrim(ft_substr((*input_str), 0, size_to_copy), " \t");
	(*input_str) += size_to_copy;
	return (mode);
}

int	set_output_mode(char **input_str, t_list_params *params_el)
{
	int 	size_to_copy;
	int 	mode;

	size_to_copy = 0;
	if (**input_str == '|')
	{
		(*input_str)++;
		return (PIPE);
	}
	if (!ft_strncmp(*input_str, ">>", 2))
		mode = REDRCT_APPEND;
	else
		mode = REDRCT_OUTPUT;
	if (mode == REDRCT_APPEND)
		(*input_str) += 2;
	else
		(*input_str)++;
	while (**input_str == ' ' || **input_str == '\t')
		(*input_str)++;
	while (!ft_chr_check(" \t><|", (*input_str)[size_to_copy]))
		size_to_copy++;
	params_el->output_file = ft_substr(*input_str, 0, size_to_copy);
	(*input_str) += size_to_copy;
	return (mode);
}

void	set_params_to_el(char **input_str, t_list_params *el)
{
	int	i;



	
	i = 0;
	while (**input_str)
	{
		if (**input_str == '<')
		{
			if (el->input_mod)
				break ;
			el->input_mod = set_input_mode(input_str, el);
		}
		if (**input_str == '|')
		{
			el->output_mode = set_output_mode(input_str, el);
			break ;
		}
		if (**input_str == '>'git)
			el->output_mode = set_output_mode(input_str, el);
		el->str_to_cmd[i++] = **input_str;
		(*input_str)++;
	}
	el->str_to_cmd[i] = '\0';
	el->cmd_arr = ft_split(ft_strtrim(el->str_to_cmd, " \t"), ' ');
	free(el->str_to_cmd);
	el->str_to_cmd = NULL;
}

int	parser(char *input_str, t_list **list)
{
	t_list_params	*el;

	while (*input_str)
	{
		el = create_empty_el();
		el->str_to_cmd = malloc(ft_strlen(input_str));
		set_params_to_el(&input_str, el);
		ft_lstadd_back(list, ft_lstnew(el));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list			*list;
////////
	argc++;
	argv++;
////////
//	char *s = "grep<lol\tnew<new.txt";
//	char *s = "ls | rev";
	char *s = "cat < intput   | rev";
	list = NULL;
	parser(s, &list);
	validation(list, envp);
	show_params(list);
	return (0);
}