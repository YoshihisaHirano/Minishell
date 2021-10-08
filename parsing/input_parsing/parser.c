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
	char	**param_to_set;

	if (params_el->input_mod)
		return (handle_token_error(input_str, **input_str));
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
		return (handle_token_error(input_str, **input_str));
	if (**input_str == '|')
	{
		params_el->output_mode = PIPE;
		(*input_str)++;
		return (1);
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


int	set_params_to_el(char **input_str, t_list_params *el, t_mshell *shell)
{
	int		i;
	int		set_mode_status;

	i = 0;
	set_mode_status = 0;
	while (**input_str)
	{
		if (**input_str == '\"' || **input_str == '\'')
			handle_quotes(input_str, el, &i);
		else if (**input_str == '<')
			set_mode_status = set_input_mode(input_str, el);
		else if (**input_str == '|' || **input_str == '>')
			set_mode_status = set_output_mode(input_str, el);
		else
		{
			el->str_to_cmd[i++] = **input_str;
			if (**input_str)
				(*input_str)++;
		}
		if (set_mode_status == -1 || set_mode_status == 1)
			return (set_mode_status);
	}
	el->str_to_cmd[i] = '\0';
	if (!shell)
		return (0);
	el->cmd_arr = parse_args(el->str_to_cmd, shell);
	return (0);
}

int	parser(char *input_str, t_list **list, t_mshell *shell)
{
	t_list_params	*el;

	while (*input_str)
	{
		el = create_empty_el();
		el->str_to_cmd = malloc(ft_strlen(input_str) + 1);
		if (set_params_to_el(&input_str, el, shell) == -1)
		{
			printf("Okay, Houston...we've had a problem here. Moon is "
				   "fucked\n");
			// get out
		}
		ft_lstadd_back(list, ft_lstnew(el));
	}
	return (0);
}

/*TODO for pipe one more handler in valid for extra pipe*/
/*TODO 'cats  "\"c\'at\"  >lol\'"  -->>str_to_cmd: |"c'at"  | output_file: |lol'| */
/*TODO validator has intput-output-||| */
/*some sega in parse env MAKEFLAGS=?????!!!!?*/
int	main(int argc, char **argv, char **envp)
{
	t_list			*list;
	t_mshell		shell;
////////
	(void)argc;
	(void)argv;
////////
	char *s = "cat input> output ";
	list = NULL;
	init_shell(&shell, envp);

	parser(s, &list, &shell);
	validation(list, envp);
	show_params(list);
	return (0);
}