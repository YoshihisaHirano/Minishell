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
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/rltypedefs.h"
# include "libft/libft.h"

#define PIPE 1
#define REDRCT_OUTPUT 2
#define REDRCT_APPEND 3
#define REDRCT_INPUT 4
#define HERE_DOC 5
#define TOKEN_SET ">|"

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

char	*ft_strndup(char *src, int size)
{
	char		*cpy_ptr;
	size_t		i;

	i = 0;
	cpy_ptr = malloc(size + 1);
	if (!cpy_ptr)
		return (NULL);
	while (i < size && src[i])
	{
		cpy_ptr[i] = src[i];
		i++;
	}
	cpy_ptr[i] = '\0';
	return (cpy_ptr);
}

typedef struct s_list_params
{
	char	**cmd_arr;
	char	*str_to_cmd;
	char	*path_app;
	int		fd[2];
	char	*here_doc_limiter;
	int		input_mod;
	int 	output_mode;
	char 	*input_file;
	char 	*output_file;
}			t_list_params;

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
	while (**input_str == ' ')
		(*input_str)++;
	while (!ft_chr_check(" ><|", (*input_str)[size_to_copy]))
		size_to_copy++;
	*param_to_set = ft_strtrim(ft_strndup((*input_str), size_to_copy), " ");
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
	while (**input_str == ' ')
		(*input_str)++;
	while (!ft_chr_check(" ><|", (*input_str)[size_to_copy]))
		size_to_copy++;
	params_el->output_file = ft_strndup((*input_str), size_to_copy);
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
		if (ft_chr_check(TOKEN_SET, **input_str))
		{
			el->output_mode = set_output_mode(input_str, el);
			break ;
		}
		el->str_to_cmd[i++] = **input_str;
		(*input_str)++;
	}
	el->str_to_cmd[i] = '\0';
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

int	main(void)
{
	t_list			*list;
	t_list *tmp;
	t_list_params *param_el;

	char *s = "cat<<lim1|kjnb>out>out2";
	char *input = ft_strdup(s);
	list = NULL;
	parser(input, &list);

	tmp = list;
	while(tmp)
	{
		printf("--------------------------\n");
		param_el = ((t_list_params *) tmp->content);
		printf("input_mod: %d\nlimiter: |%s|\ninput_file: |%s|\ntmp_str:"
			   "|%s|\noutput_mode: %d\noutput_file:|%s|\n",
			   param_el->input_mod,
			   param_el->here_doc_limiter, param_el->input_file,
			   param_el->str_to_cmd, param_el->output_mode, param_el->output_file);
		tmp = tmp->next;
	}
	return (0);
}