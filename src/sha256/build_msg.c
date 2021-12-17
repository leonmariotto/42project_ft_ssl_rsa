/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:02:22 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/13 09:37:22 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

u_int64_t        build_msg(char **pmsg, char *msg, u_int64_t len, int invert)
{
    u_int64_t   i;
    u_int64_t   plen;

    plen = (len % 64 < 56 ? len + (64 - len % 64) : len + (64 - len % 64) + 64);
    if (!(*pmsg = malloc(plen)))
        return (0);
    ft_memcpy(*pmsg, msg, len);
    i = len;
    (*pmsg)[i++] = (u_int8_t)0x80;
    while (i < plen)
    {
        (*pmsg)[i++] = 0;
    }
	*(u_int64_t *)(*pmsg + i - 8) =
		invert ? 8 * len : ft_bswap_uint64(8 * len);
    return (plen);
}
