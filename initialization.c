/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:26:36 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/24 18:26:36 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_func(t_builtins *builtin)
{
	if (!ft_strncmp(builtin->name, "echo", ft_strlen(builtin->name)))
		builtin->func = my_echo;
	if (!ft_strncmp(builtin->name, "env", ft_strlen(builtin->name)))
		builtin->func = my_env;
	if (!ft_strncmp(builtin->name, "pwd", ft_strlen(builtin->name)))
		builtin->func = my_pwd;
	if (!ft_strncmp(builtin->name, "cd", ft_strlen(builtin->name)))
		builtin->func = my_cd;
	if (!ft_strncmp(builtin->name, "export", ft_strlen(builtin->name)))
		builtin->func = my_export;
	if (!ft_strncmp(builtin->name, "unset", ft_strlen(builtin->name)))
		builtin->func = my_unset;
	if (!ft_strncmp(builtin->name, "exit", ft_strlen(builtin->name)))
		builtin->func = my_exit;
}

void	init_builtins(t_mshell *shell)
{
	char		*names;
	char		**splt_names;
	int			i;
	t_builtins	*bn;
	t_list		*elt;

	names = "echo env pwd cd export unset exit";
	splt_names = ft_split(names, ' ');
	if (!splt_names)
		error_exit(NULL);
	i = 0;
	while (i < 7)
	{
		bn = malloc(sizeof(t_builtins));
		bn->name = splt_names[i];
		assign_func(bn);
		elt = ft_lstnew(bn);
		ft_lstadd_back(&shell->builtins, elt);
		i++;
	}
}

void	init_shell(t_mshell *shell, char **env)
{
	*shell = (t_mshell){.last_exit_code = 0, .env_copy = NULL,
						.builtins = NULL};
	parse_env(shell, env);
	//TODO SHLVL+=1
	init_builtins(shell);
	handle_sigs();
}