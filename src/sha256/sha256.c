/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:16:17 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 12:23:37 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "consts_sha256.h"

void        compute_w(u_int32_t *w, char *buf)
{
    int             i;
    u_int32_t       s[2];

    i = 0;
    ft_bzero(w, 64 * 4);
    while (i < 64)
    {
        if (i < 16)
            w[i] = ft_bswap_uint32(((u_int32_t*)buf)[i]);
        else
        {
            s[0] = ft_rightrotate32(w[i - 15], 7) ^
                ft_rightrotate32(w[i - 15], 18) ^ (w[i - 15] >> 3);
            s[1] = ft_rightrotate32(w[i - 2], 17) ^
                ft_rightrotate32(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s[0] + w[i - 7] + s[1];
        }
        ++i;
    }
}

void        compression_main_loop(u_int32_t *w, u_int32_t *wvars)
{
    u_int32_t       s[2];
    u_int32_t       ch;
    u_int32_t       maj;
    u_int32_t       temp[2];
    int             i;

    i = -1;
    while (++i < 64)
    {
        s[1] = ft_rightrotate32(wvars[4], 6) ^ ft_rightrotate32(wvars[4], 11) ^
                ft_rightrotate32(wvars[4], 25);
        ch = (wvars[4] & wvars[5]) ^ ((~wvars[4]) & wvars[6]);
        temp[0] = wvars[7] + s[1] + ch + Ksha256[i] + w[i];
        s[0] = ft_rightrotate32(wvars[0], 2) ^ ft_rightrotate32(wvars[0], 13) ^
                ft_rightrotate32(wvars[0], 22);
        maj = (wvars[0] & wvars[1]) ^ (wvars[0] & wvars[2]) ^
                (wvars[1] & wvars[2]);
        temp[1] = s[0] + maj;
        wvars[7] = wvars[6];
        wvars[6] = wvars[5];
        wvars[5] = wvars[4];
        wvars[4] = wvars[3] + temp[0];
        wvars[3] = wvars[2];
        wvars[2] = wvars[1];
        wvars[1] = wvars[0];
        wvars[0] = temp[0] + temp[1];
    }

}

void        process_sha256(char *buf, unsigned int *vars)
{
    u_int32_t       w[64];
    u_int32_t       wvars[8];

    compute_w(w, buf);
    ft_memcpy(wvars, vars, 32);
    compression_main_loop(w, wvars);
    vars[0] += wvars[0];
    vars[1] += wvars[1];
    vars[2] += wvars[2];
    vars[3] += wvars[3];
    vars[4] += wvars[4];
    vars[5] += wvars[5];
    vars[6] += wvars[6];
    vars[7] += wvars[7];
}

unsigned int        *sha256_do_ops(char *pmsg, u_int64_t plen)
{
    unsigned int     i;
    char            buf[64];
    unsigned int    *vars;

    if (!(vars = (unsigned int *)malloc(sizeof(int) * 8)))
        return (NULL);
    ft_memcpy(vars, ivsha256, sizeof(ivsha256));
    i = 0;
    while (i < plen / 64)
    {
        ft_memcpy(buf, pmsg + i * 64, 64);
        process_sha256(buf, vars);
        ++i;
    }
    return (vars);
}

unsigned char         *sha256(char *msg, int len)
{
    char        *pmsg;
    u_int64_t   plen;
    unsigned int    *vars;
    int             i;

    if (!(plen = build_msg(&pmsg, msg, len, 0)))
        return (0);
    vars = sha256_do_ops(pmsg, plen);
    free(pmsg);
    i = -1;
    while (++i < 8)
        vars[i] = ft_bswap_uint32((u_int32_t)vars[i]);
    return ((unsigned char*)vars);
}
