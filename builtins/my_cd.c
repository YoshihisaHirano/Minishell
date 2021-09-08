/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                                                 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:15:34 by aalannys                      #+#    #+#             */
/*   Updated: 2021/09/08 14:15:34 by aalannys                    ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pwds(t_mshell *shell) /* sets pwds if they are unset */
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*curr_path;

	curr_path = NULL;
	curr_path = getcwd(NULL, 1);
	pwd = get_by_key(shell, "PWD");
	if (!pwd)
		add_var(shell, "PWD", curr_path);
	old_pwd = get_by_key(shell, "OLDPWD");
	if (!old_pwd)
		add_var(shell, "OLDPWD", ft_strdup(curr_path));
}

int	my_cd(t_mshell *shell, char *path)
{
	int		res;
	char	*curr_path;
	t_list	*pwd;
	char	*old_pwd_val;

	check_pwds(shell);
	res = chdir(path);
	if (res == -1)
	{
		print_error("cd");
		shell->last_exit_code = 1;
		return (1);
	}
	curr_path = NULL;
	curr_path = getcwd(curr_path, 1);
	pwd = get_by_key(shell, "PWD");
	old_pwd_val = ((t_envvar *)(pwd->content))->value;
	set_by_key(shell, "OLDPWD", old_pwd_val);
	set_by_key(shell, "PWD", curr_path);
	return (0);
}
