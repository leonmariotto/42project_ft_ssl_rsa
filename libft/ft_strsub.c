/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:33 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:33 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *buff;

	if (!s)
		return (NULL);
	if (!(buff = (char*)malloc(len + 1)))
		return (NULL);
	ft_strncpy(buff, s + start, len);
	buff[len] = '\0';
	return (buff);
}
