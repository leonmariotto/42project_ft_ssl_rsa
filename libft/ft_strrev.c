/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:19:17 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:18 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	swap;

	i = -1;
	len = ft_strlen(s) - 1;
	while (++i <= len / 2)
	{
		swap = *(s + i);
		*(s + i) = *(s + (len - i));
		*(s + (len - i)) = swap;
	}
	return (s);
}
