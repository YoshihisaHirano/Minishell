/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:06:44 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/05 12:06:44 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO add signal handling in fork?
// TODO should change last exit code to 1?
void	ctl_c_handle(int x)
{
	(void)x;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	last_exit_code = 1;
}

void	handle_sigs(void)
{
//	rl_catch_signals = 0; TODO find out wtf is this
	signal(SIGINT, ctl_c_handle);
	signal(SIGQUIT, SIG_IGN);
}