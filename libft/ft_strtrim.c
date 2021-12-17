/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:40 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:41 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*buff;
	size_t	i;

	if (!s)
		return (NULL);
	while (ft_isspace(*s))
		++s;
	i = 0;
	if (*s)
	{
		i = ft_strlen(s);
		while (ft_isspace(s[i - 1]) && i - 1 > 0)
			--i;
	}
	if (!(buff = (char*)malloc(i + 1)))
		return (0);
	ft_strncpy(buff, s, i);
	buff[i] = '\0';
	return (buff);
}
