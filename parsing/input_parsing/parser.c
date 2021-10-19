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

#include "../../minishell.h"

//int	validation(t_list *param_list, char **envp);

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
		if (param_el->builtin)
			printf("Has builtin\n");
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
		if (param_el->input)
		{
			t_list *tmp_input = param_el->input;
			t_list_io_params *tmp_io_el;
			while (tmp_input)
			{
				tmp_io_el = (t_list_io_params *) tmp_input->content;
				printf("input: %s---%s\n", tmp_io_el->file_name,
					   modes[tmp_io_el->mode]);
				tmp_input = tmp_input->next;
			}
		}
		if (param_el->output)
		{
			t_list *tmp_output = param_el->output;
			t_list_io_params *tmp_io_el;
			while (tmp_output)
			{
				tmp_io_el = (t_list_io_params *) tmp_output->content;
				printf("output: %s---%s\n", tmp_io_el->file_name,
					   modes[tmp_io_el->mode]);
				tmp_output = tmp_output->next;
			}
		}
		tmp = tmp->next;
	}
	printf("--------------------------\n");
}

int	set_input_mode(char **input_str, t_mshell *shell, t_list_io_params *io_el)
{
	while (ft_isspace(**input_str))
		(*input_str)++;
	if (!ft_strncmp(*input_str, "<<", 2))
	{
		io_el->mode = HERE_DOC;
		(*input_str) += 2;
	}
	else
	{
		io_el->mode = REDRCT_INPUT;
		(*input_str)++;
	}
	if (get_io_name(&(io_el->file_name), input_str) == -1)
		return (-1);
	if (!io_el->file_name || !*(io_el->file_name))
		return (handle_token_error(input_str, **input_str));
	process_io_tokens(&(io_el->file_name), shell, io_el->mode);
	while (ft_isspace(**input_str))
		(*input_str)++;
	return (0);
}

int	set_output_mode(char **input_str, t_mshell *shell, t_list_io_params *io_el)
{
	while (ft_isspace(**input_str))
		(*input_str)++;
	if (**input_str == '|')
	{
		io_el->mode = PIPE;
		(*input_str)++;
		return (PIPE);
	}
	if (!ft_strncmp(*input_str, ">>", 2))
		io_el->mode = REDRCT_APPEND;
	else
		io_el->mode = REDRCT_OUTPUT;
	if (io_el->mode == REDRCT_APPEND)
		(*input_str) += 2;
	else
		(*input_str)++;
	if (get_io_name(&(io_el->file_name), input_str) == -1)
		return (-1);
	if (!io_el->file_name || !*(io_el->file_name))
		return (handle_token_error(input_str, **input_str));
	process_io_tokens(&(io_el->file_name), shell, io_el->mode);
	while (ft_isspace(**input_str))
		(*input_str)++;
	return (0);
}

int	token_process(char **input_str, t_mshell *shell, int(*set_io)(char **,
		t_mshell*, t_list_io_params*), t_list_params *el)
{
	t_list_io_params	*io_el;
	int					set_mode_status;

	el->str_to_cmd[el->cmd_str_i] = ' ';
	el->cmd_str_i++;
	io_el = malloc(sizeof(t_list_io_params));
	io_el->file_name = NULL;
	io_el->fd = -1;
	set_mode_status = set_io(input_str, shell, io_el);
	if (set_io == set_output_mode)
		ft_lstadd_back(&(el->output), ft_lstnew(io_el));
	else
		ft_lstadd_back(&(el->input), ft_lstnew(io_el));
	return (set_mode_status);
}

int	set_params_to_el(char **input_str, t_list_params *el, t_mshell *shell)
{
	int		set_mode_res;

	el->cmd_str_i = 0;
	set_mode_res = 0;
	while (**input_str)
	{
		if (**input_str == '\"' || **input_str == '\'')
			handle_quotes(input_str, el);
		while (!set_mode_res && **input_str && **input_str == '<')
			set_mode_res = token_process(input_str, shell, set_input_mode, el);
		while (!set_mode_res && **input_str
			&& (**input_str == '|' || **input_str == '>'))
			set_mode_res = token_process(input_str, shell, set_output_mode, el);
		if (set_mode_res == -1 || set_mode_res == PIPE)
			break ;
		el->str_to_cmd[el->cmd_str_i++] = **input_str;
		if (**input_str && **input_str != '|')
			(*input_str)++;
	}
	el->str_to_cmd[el->cmd_str_i] = '\0';
	if (check_for_cmd(el->str_to_cmd))
		return (-1);
	el->cmd_arr = parse_args(el->str_to_cmd, shell);
	return (set_mode_res);
}

int	parser(char *input_str, t_list **list, t_mshell *shell)
{
	t_list_params	*el;

	while (*input_str)
	{
		el = malloc(sizeof(t_list_params));
		el->path_app = NULL;
		el->cmd_arr = NULL;
		el->input = NULL;
		el->output = NULL;
		el->builtin = NULL;
		el->str_to_cmd = malloc(ft_strlen(input_str) * 2 + 1);
		if (!el->str_to_cmd)
			return (-1);
		if (set_params_to_el(&input_str, el, shell) == -1)
		{
			ft_lstadd_back(list, ft_lstnew(el));
			return (-1);
		}
		ft_lstadd_back(list, ft_lstnew(el));
	}
	return (0);
}

/*TODO for pipe one more handler in valid for extra pipe*/

/*???TODO WTF "\'cat>>fil\"e args\' args" not to args. only one string??????*/
/*TODO WTF "cat file>out | rev  -> create file with content and exec cmd"*/
/*TODO if pipe without any cmd, prev cmd execute and then throw error*/
