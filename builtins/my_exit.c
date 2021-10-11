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
	ft_lstclear(&shell->builtins, free_builtins);
	rl_clear_history();
//	write(1, "exit\n", 5);
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
	code = ft_atoi_ll(arg);
	if (code >= 0 || (is_minus == -1 && code == LLONG_MIN))
	{
		*exit_code = (unsigned char)(code * is_minus);
		return (ARG_OK);
	}
	*exit_code = 255;
	return (NOT_NUMERIC);
}

void	my_exit(t_mshell *shell, char **cmd_arr)
{
	//check num, error if > than signed long long && error if arg is not
	// numeric are the same
	// if ar is not numeric it still quits bash (255) but if there are other
	// args after the number, it doesn't quit
	int exit_code;
	int res;

	exit_code = g_last_exit_code;
	res = check_arg(cmd_arr[1], &exit_code);
	if (res == NOT_NUMERIC)
	{
		exit_routine(shell);
		print_err_msg("exit", cmd_arr[1], "numeric argument required");
		exit(exit_code);
	}
	if (res == ARG_OK && chr_arr_len(cmd_arr) <= 2)
	{
		exit_routine(shell);
		exit(exit_code);
	}
	print_err_msg("exit", NULL, "too many arguments");
	g_last_exit_code = 1;
}