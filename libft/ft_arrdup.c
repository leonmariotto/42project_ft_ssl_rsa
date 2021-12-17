/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:06:40 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:06:41 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_arrdup(void **arr, const size_t content_size)
{
	size_t	len;
	void	**a;
	size_t	i;

	if (!arr)
		return (NULL);
	len = ft_arrlen(arr);
	if (!(a = (void **)ft_memalloc(sizeof(void *) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!(a[i] = malloc(content_size)))
		{
			ft_arrfree(a);
			return (NULL);
		}
		ft_memcpy(a[i], arr[i], content_size);
		++i;
	}
	return (a);
}
