/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:12:56 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:12:57 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*buff;
	size_t	i;

	if (!(buff = malloc(size)))
		return (0);
	i = 0;
	while (i < size)
	{
		*((char*)buff + i) = 0;
		++i;
	}
	return (buff);
}
