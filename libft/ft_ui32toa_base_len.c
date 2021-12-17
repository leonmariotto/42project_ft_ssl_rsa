/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui32toa_base_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 08:14:31 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/03 08:59:00 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char            *ft_ui32toa_base_len(u_int32_t n, int base, int len)
{
    char    *ret;
    u_int32_t     tmp;

    if (base < 2)
        return (NULL);
    if (!(ret = (char*)malloc(1 + len)))
        return (NULL);
    ret[len--] = 0;
    while (n && len >= 0)
    {
        tmp = n % base;
        n /= base;
        ret[len--] = (tmp > 9 ? 'a' + (tmp - 10) : '0' + tmp);
    }
    while (len >= 0)
        ret[len--] = '0';
    return (ret);
}
