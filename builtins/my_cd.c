/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:15:34 by aalannys           #+#    #+#            */
/*   Updated: 2021/09/08 14:15:34 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pwds(t_mshell *shell) /* sets pwds if they are unset */
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*curr_path;

	curr_path = NULL;
	curr_path = getcwd(NULL, 1);
	if (!curr_path)
	{
		print_error("cd", shell, NULL);
		return (1);
	}
	pwd = get_by_key(shell, "PWD");
	if (!pwd)
		add_var(shell, "PWD", curr_path);
	old_pwd = get_by_key(shell, "OLDPWD");
	if (!old_pwd)
		add_var(shell, "OLDPWD", ft_strdup(curr_path));
	return (0);
}

int	use_chdir(t_mshell *shell, char **cmd_arr)
{
	t_list	*elt;
	int		res;

	elt = get_by_key(shell, "HOME");
	if (!cmd_arr[1] && !elt)
	{
		print_err_msg("cd", NULL, "HOME not set");
		return (-1);
	}
	if (cmd_arr[1])
		res = chdir(cmd_arr[1]);
	else
		res = chdir(((t_envvar *)(elt->content))->value);
	if (res == -1)
		print_error("cd", shell, cmd_arr[1]);
	return (res);
}

void	my_cd(t_mshell *shell, char **cmd_arr)
{
	int		res;
	char	*curr_path;
	t_list	*pwd;

	if (check_pwds(shell))
		return ;
	res = use_chdir(shell, cmd_arr);
	if (res == -1)
		return ;
	curr_path = NULL;
	curr_path = getcwd(curr_path, 1);
	if (!curr_path)
	{
		print_error("cd", shell, NULL);
		return ;
	}
	pwd = get_by_key(shell, "PWD");
	set_by_key(shell, "OLDPWD", ((t_envvar *)(pwd->content))->value);
	set_by_key(shell, "PWD", curr_path);
	shell->last_exit_code = 0;
}
