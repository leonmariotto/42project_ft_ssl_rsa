/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_casinsens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:05:36 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:05:37 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmpcase(char c1, char c2)
{
	if (ft_islower(c1) && ft_isupper(c2))
		return ((unsigned char)(c1 - 32) - (unsigned char)c2);
	else if (ft_isupper(c1) && ft_islower(c2))
		return ((unsigned char)(c1 + 32) - (unsigned char)c2);
	else
		return ((unsigned char)c1 - (unsigned char)c2);
}

int			ft_strcmpcase(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (*(s1 + i) == *(s2 + i) && (*(s2 + i) && *(s1 + i)))
		i++;
	return (cmpcase(*(s1 + i), *(s2 + i)));
}
