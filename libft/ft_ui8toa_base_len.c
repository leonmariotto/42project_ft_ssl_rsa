/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint8_base_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:42:40 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 11:45:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char            *ft_ui8toa_base_len(u_int8_t n, int base, int len)
{
    char    *ret;
    u_int8_t     tmp;

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
