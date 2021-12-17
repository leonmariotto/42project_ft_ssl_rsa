/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:15:42 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:15:43 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort(void **arr, size_t size, int (*f)(void*, void*))
{
	size_t	i;
	size_t	j;
	void	*k;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size)
		{
			if (f(arr[i], arr[j]) > 0)
			{
				k = arr[i];
				arr[i] = arr[j];
				arr[j] = k;
			}
			++j;
		}
		++i;
	}
}
