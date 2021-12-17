/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ahextovbin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:37:37 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/06 18:38:01 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

u_int8_t    *ft_ahextovbin(char *str, int len)
{
    int         i;
    int         j;
    u_int8_t    *ret;
    char        buf[3];

    i = -1;
    while (str[++i])
        str[i] = ft_tolower(str[i]);
    if (!(ret = ft_memalloc(len + 1)))
        return (NULL);
    i = 0;
    j = 0;
    ft_bzero(buf, 3);
    while (str[i] && j < len)
    {
        ft_strncpy(buf, &(str[i]), 2);
        if (!buf[1])
            buf[1] = '0';
        ret[j++] = ft_atoibase(buf, "0123456789abcdef");
        ft_bzero(buf, 3);
        i += 2;
    }
    while (j < len)
    {
        ret[j++] = 0;
    }
    return (ret);
}
