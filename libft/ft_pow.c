/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:14:19 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:14:21 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int n, unsigned int factor)
{
	unsigned int	i;
	int				j;

	if (factor == 0)
		return (TRUE);
	i = 0;
	j = 1;
	while (i < factor)
	{
		j *= n;
		++i;
	}
	return (j);
}
