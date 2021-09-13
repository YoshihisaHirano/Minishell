/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:25:44 by aalannys            #+#    #+#           */
/*   Updated: 2021/09/13 15:25:44 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_args()

char	**parse_args(char *args, t_mshell *shell)
{
	char	*preprocessed;
	char	**res;

	if (check_quotes(args, shell))
		return (NULL);
	preprocessed = preprocessor(args, shell);
	res = split_args(preprocessed, shell);
	remove_quotes(res);
	return (res);
}