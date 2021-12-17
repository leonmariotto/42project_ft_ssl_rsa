/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:07:24 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/06 22:11:13 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void                *ft_memdup(char *src, int n)
{
    int     i;
    char    *ptr;

    i = -1;
    if (!src || !n)
        return (NULL);
    if (!(ptr = (char *)malloc(n)))
        return (NULL);
    while (++i < n)
        ptr[i] = src[i];
    return (ptr);
}
