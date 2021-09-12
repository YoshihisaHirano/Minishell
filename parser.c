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
#define TOKEN_SET "<>| "

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
	char 	*input_file;
	int 	output_mode;

}							t_list_params;

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
	return (el);
}

/*  cat << stop ....
 *  <fileinput
 *  << LIMITER
 * */
int	check_for_input_mode(char **input_str, t_list_params *params_el)
{
	char	*input_str_ptr;
	int 	size_to_copy;

	input_str_ptr = *input_str;
	size_to_copy = 0;
	if (!ft_strncmp(input_str_ptr, "<<", 2))
	{
		input_str_ptr += 2;
		while (input_str_ptr[size_to_copy] == ' ')
			size_to_copy++;
		while (input_str_ptr[size_to_copy] != ' ')
			size_to_copy++;
		params_el->here_doc_limiter = ft_strtrim(ft_strndup(input_str_ptr,
															size_to_copy), " ");
		(*input_str) += size_to_copy + 2;
		return (HERE_DOC);
	}
	if (*input_str_ptr ==  '<')
	{
		input_str_ptr++;
		while (input_str_ptr[size_to_copy] == ' ')
			size_to_copy++;
		while(!size_to_copy || input_str_ptr[size_to_copy] != ' ')
			size_to_copy++;
		params_el->input_file = ft_strtrim(ft_strndup(input_str_ptr,
													  size_to_copy), " ");
		(*input_str) += size_to_copy + 2;
		return (REDRCT_INPUT);
	}
	return (0);
}

int	parser(char *input_str, t_list **list)
{
	t_list_params	*el;
	char			*input_ptr;
	int 	i;
	int		on_current_el;

	input_ptr = input_str;
	while (*input_ptr)
	{
		i = 0;
		on_current_el = 1;
		el = create_empty_el();
		el->str_to_cmd = malloc(ft_strlen(input_str));
		while (on_current_el && *input_ptr)
		{
			if (*input_ptr == '<')
			{
				el->input_mod = check_for_input_mode(&input_ptr, el);
				ft_lstadd_back(list, ft_lstnew(el));
			}
			el->str_to_cmd[i++] = *input_ptr;
			if (ft_strchr("|>", *input_ptr))
			{
				on_current_el = 0;
				// set_output
			}
			input_ptr++;
		}
		el->str_to_cmd[i++] = ' ';
		el->str_to_cmd[i] = '\0';
	}

//	while (*input_ptr)
//	{
//		el = create_empty_el();
//		el->str_to_cmd = malloc(ft_strlen(input_str));
//		if (*input_ptr == '<')
//		{
//			el->input_mod = check_for_input_mode(&input_ptr, el);
//			ft_lstadd_back(list, ft_lstnew(el));
//		}
//		if (*input_ptr == '>')
//			printf("> mode here\n");
//		if (*input_ptr == '|')
//			printf("pipe detected\n");
//		while (*input_ptr == ' ')
//			input_ptr++;
//		while (!ft_strchr(TOKEN_SET, *input_ptr))
//		{
//			el->str_to_cmd[i++] = *input_ptr;
//			input_ptr++;
//		}
//		el->str_to_cmd[i++] = ' ';
//		el->str_to_cmd[i++] = '\0';
//		input_ptr++;
//	}

	free(input_str);
	return (0);
}

int	main(void)
{
	t_list			*list;
	t_list *tmp;
	t_list_params *param_el;


	char *s = "cat <<stop";
	char *input = ft_strdup(s);
	list = NULL;
	parser(input, &list);

	tmp = list;
	printf("--------------------------\n");
	while(tmp)
	{
		param_el =  ((t_list_params *) tmp->content);
		printf("input_mod: %d\nlimiter: %s\ninputfile: %s\ntmp_str: %s\n",
			   param_el->input_mod,
			   param_el->here_doc_limiter, param_el->input_file, param_el->str_to_cmd);
		tmp = tmp->next;
	}
	return (0);
}