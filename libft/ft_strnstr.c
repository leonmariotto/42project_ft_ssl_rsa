/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:03 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:04 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char*)haystack);
	i = 0;
	while (*haystack && i < len)
	{
		j = 0;
		while (needle[j])
		{
			if (haystack[j] == '\0' || i + j >= len)
				return (NULL);
			if (haystack[j] != needle[j])
				break ;
			++j;
		}
		if (needle[j] == '\0')
			return ((char*)haystack);
		++haystack;
		++i;
	}
	return (NULL);
}
