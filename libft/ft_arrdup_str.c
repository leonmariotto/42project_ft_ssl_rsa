/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:03:35 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:03:39 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup_str(char **arr)
{
	size_t	len;
	char	**a;
	size_t	i;
	size_t	l;

	if (!arr)
		return (NULL);
	len = ft_arrlen((void **)arr);
	if (!(a = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		l = ft_strlen(arr[i]);
		if (!(a[i] = (char *)ft_strnew(l)))
		{
			ft_arrfree((void **)a);
			return (NULL);
		}
		ft_memcpy(a[i], arr[i], l);
		++i;
	}
	return (a);
}
