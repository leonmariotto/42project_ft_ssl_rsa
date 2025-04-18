/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:10:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:10:31 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_size(const char *base)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (*(base + i))
	{
		if (*(base + i) == '+' || *(base + i) == '-')
			return (0);
		while (*(base + j))
		{
			if (j == i)
				j++;
			if (*(base + i) == *(base + j) && j == 1)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

char		*ft_itoabase(int n, const char *base)
{
	char	*res;
	int		i;
	long	n2;

	if (base_size(base) < 2)
		return ("\0");
	res = ft_strnew(33);
	i = 0;
	n2 = n;
	if (n < 0)
		n2 = n * -1;
	while ((n2 / base_size(base)) > 0)
	{
		*(res + i) = *(base + (n2 % base_size(base)));
		n2 /= base_size(base);
		i++;
	}
	*(res + i) = *(base + (n2 % base_size(base)));
	i++;
	if (n < 0)
		*(res + i++) = '-';
	ft_strrev(res);
	return (res);
}
