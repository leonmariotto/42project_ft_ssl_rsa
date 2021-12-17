/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:07:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:07:30 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_arrremove(void **arr, const size_t index)
{
	if (!arr)
		return (NULL);
	free((void *)arr[index]);
	ft_memmove(arr + index, arr + index + 1,
		sizeof(void *) * (ft_arrlen(arr) - index));
	return (arr);
}
