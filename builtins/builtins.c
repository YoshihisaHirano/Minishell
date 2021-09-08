/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:26:58 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/07 16:26:58 by aalannys           ###    #######.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_env(t_mshell *shell)
{
	ft_lstiter(shell->env_copy, print_node); //TODO error on arguments present
}

void	my_pwd(t_mshell *shell) //TODO error on arguments present
{
	t_list	*node;

	node = get_by_key(shell, "PWD");
	if (((t_envvar *)(node->content))->value)
		printf("%s\n", ((t_envvar *)(node->content))->value);
	else
		printf("\n");
}

int	my_cd(t_mshell *shell, char *path)
{
	DIR		*cd_dir;
	t_list	*old_pwd;
	char	*old_pwd_val;

	cd_dir = opendir(path);
	if (!cd_dir)
	{
		print_error("cd");
		shell->last_exit_code = errno;
		return (1);
	}
	// TODO what if pwd and oldpwd are unset?
	old_pwd = get_by_key(shell, "PWD");
	old_pwd_val = ((t_envvar *)(old_pwd->content))->value;
	set_by_key(shell, "OLDPWD", old_pwd_val);
	set_by_key(shell, "PWD", ft_strdup(path));
	closedir(cd_dir);
	return (0);
}