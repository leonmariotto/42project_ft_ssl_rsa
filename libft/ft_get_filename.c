/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:08:35 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:08:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_filename(const char *path)
{
	char *s;

	if (!(s = ft_strrchr(path, '/')))
		return (ft_strdup(path));
	if (!s || !s[1])
		return (ft_strnew(0));
	return (ft_strdup(s + 1));
}
