/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:13:17 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:13:22 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((char*)s1) == *((char*)s2) && i < n - 1)
	{
		++s1;
		++s2;
		++i;
	}
	return (*((unsigned char*)s1) - *((unsigned char*)s2));
}
