/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:07:56 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:07:58 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	int	n;
	int	neg;

	if (!str)
		return (0);
	while (*str && (*str == ' ' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\f' || *str == '\v'))
		++str;
	neg = (*str == '-');
	if (*str == '+' || *str == '-')
		++str;
	n = 0;
	while (*str >= '0' && *str <= '9')
	{
		n *= 10;
		n += *str - '0';
		++str;
	}
	return (neg ? -n : n);
}
