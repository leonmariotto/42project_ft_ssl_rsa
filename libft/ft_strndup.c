/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:18:21 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:18:22 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char *buff;

	if (!s || !n)
		return (NULL);
	if (!(buff = ft_strnew(n)))
		return (NULL);
	return (ft_strncpy(buff, s, n));
}
