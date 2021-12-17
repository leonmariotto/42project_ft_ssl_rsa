/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:10:49 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:10:50 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_last_char(const char *str)
{
	size_t len;

	if ((len = ft_strlen(str)) == 0)
		return (0);
	return (str[len - 1]);
}
