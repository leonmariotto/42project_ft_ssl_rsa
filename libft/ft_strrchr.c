/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:13 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:13 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const *last;

	if (!s)
		return (NULL);
	last = 0;
	while (1)
	{
		if (*s == c)
			last = s;
		if (*s == '\0')
			break ;
		++s;
	}
	return ((char*)last);
}
