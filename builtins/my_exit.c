/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:22:47 by aalannys          #+#    #+#             */
/*   Updated: 2021/09/23 14:22:47 by aalannys          ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_is_numeric(char *str)
{
	while (*str)
	{
		if(!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exit_routine(t_mshell *shell)
{
	ft_lstclear(&shell->env_copy, free_node);
	ft_lstclear(&shell->cmds, free_params_lst);
//	rl_clear_history();
	write(1, "exit", 4);
}

int	check_arg(char *arg, int *exit_code)
{
	int			is_minus;
	long long	code;

	is_minus = 1;
	if (!arg)
		return (ARG_OK);
	if (*arg == '-')
		is_minus *= -1;
	if (*arg == '+' || *arg == '-')
		arg++;
	if (ft_strlen(arg) > 20 || !arg_is_numeric(arg))
	{
		*exit_code = 255;
		return (NOT_NUMERIC);
	}
	code = ft_atoi_ul(arg);
	if (code < 0 && code != LLONG_MIN)
	{
		*exit_code = 255;
		return (NOT_NUMERIC);
	}
	*exit_code = (unsigned char)code;
	return (ARG_OK);
}

void	my_exit(t_mshell *shell, t_list_params *params)
{ //TODO full memory clear, not only env (?)
	//check num, error if > than signed long long && error if arg is not
	// numeric are the same
	// if ar is not numeric it still quits bash (255) but if there are other
	// args after the number, it doesn't quit
	int exit_code;
	int res;

	exit_code = shell->last_exit_code;
	res = check_arg(params->cmd_arr[1], &exit_code);
	if (res == NOT_NUMERIC)
	{
		exit_routine(shell);
		print_err_msg("exit", params->cmd_arr[1], "numeric argument required");
		exit(exit_code);
	}
	if (res == ARG_OK && chr_arr_len(params->cmd_arr) <= 2)
	{
		exit_routine(shell);
		exit(exit_code);
	}
	print_err_msg("exit", NULL, "too many arguments");
}