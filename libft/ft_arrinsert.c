/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:07:09 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:07:11 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_arrinsert(void **arr, void *element)
{
	size_t	len;
	void	**a;

	len = (arr ? ft_arrlen(arr) : 0);
	if (!(a = (void **)malloc(sizeof(void *) * (len + 2))))
		return (NULL);
	if (arr)
		ft_memcpy(a, arr, sizeof(void *) * (len + 1));
	a[len] = element;
	a[len + 1] = NULL;
	if (arr)
		free((void *)arr);
	return (a);
}
