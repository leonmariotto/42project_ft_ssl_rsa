/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:27 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:28 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;

	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack)
	{
		i = 0;
		while (1)
		{
			if (needle[i] == '\0')
				return ((char*)haystack);
			if (haystack[i] != needle[i])
				break ;
			++i;
		}
		++haystack;
	}
	return (0);
}
