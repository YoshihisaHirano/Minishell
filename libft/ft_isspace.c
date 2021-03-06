/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:28:53 by aalannys          #+#    #+#             */
/*   Updated: 2021/10/12 16:32:16 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == '\r' || c == '\f' || c == '\t' || c == '\v'
		|| c == ' ' || c == '\n')
		return (1);
	return (0);
}
