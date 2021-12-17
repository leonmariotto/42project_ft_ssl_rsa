/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:13:39 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:13:40 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (src < dst)
	{
		i = 0;
		while (i < len)
		{
			*((char*)dst + (len - i - 1)) = *((char*)src + (len - i - 1));
			++i;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
