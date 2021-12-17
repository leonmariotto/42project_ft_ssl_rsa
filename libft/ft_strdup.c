/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:16:46 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:16:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*buff;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1) + 1;
	if (!(buff = (char*)malloc(i)))
		return (NULL);
	ft_strcpy(buff, s1);
	return (buff);
}
