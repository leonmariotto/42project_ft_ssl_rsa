/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:18:42 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 11:56:20 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "consts_md5.h"
#include <stdio.h>


static int         get_f(u_int32_t *vc, u_int32_t *words, u_int32_t i)
{
    u_int32_t       F;
    u_int32_t       g;

    if (i <= 15)
    {
        F = (vc[1] & vc[2]) | ((~vc[1]) & vc[3]);
        g = i;
    }
    else if (i <= 31)
    {
        F = (vc[3] & vc[1]) | ((~vc[3]) & vc[2]);
        g = (5 * i + 1) % 16;
    }
    else if (i <= 47)
    {
        F = vc[1] ^ vc[2] ^ vc[3];
        g = (3 * i + 5) % 16;
    }
    else
    {
        F = vc[2] ^ (vc[1] | (~vc[3]));
        g = (7 * i) % 16;
    }
    F += vc[0] + Kmd5[i] + words[g];
    return (F);
}

/*
** process_md5 : Applique les opérations de l'algorithme de hachage md5 sur un
** bloc de 512 bits.
*/ 

void         process_md5(char *buf, unsigned int *vars)
{
    u_int32_t       i;
    u_int32_t       F;
    u_int32_t       vc[4];
    u_int32_t       words[16];

    ft_memcpy(words, buf, 64);
    ft_memcpy(vc, vars, sizeof(int) * 4);
    i = -1;
    while (++i < 64)
    {
        F = get_f(vc, words, i);
        vc[0] = vc[3];
        vc[3] = vc[2];
        vc[2] = vc[1];
        vc[1] = vc[1] + ft_leftrotate32(F, Rmd5[i]);
    }
    vars[0] += vc[0];
    vars[1] += vc[1];
    vars[2] += vc[2];
    vars[3] += vc[3];
}

unsigned int        *md5_do_ops(char *pmsg, int plen)
{
    int     i;
    char    buf[64];
    unsigned int     *vars;

    if (!(vars = malloc(sizeof(int) * 4)))
        return (NULL);
    ft_memcpy(vars, ivmd5, sizeof(ivmd5));
    i = 0;
    while (i < plen / 64)
    {
        ft_memcpy(buf, pmsg + i * 64, 64);
        process_md5(buf, vars);
        ++i;
    }
    return (vars);
}

unsigned char         *md5(char *msg, int len)
{
    char            *pmsg;
    u_int64_t       plen;
    unsigned int    *vars;
//    int             i;

    pmsg = NULL;
    if (!(plen = build_msg(&pmsg, msg, len, 1)))
        return (NULL);
    if (!(vars = md5_do_ops(pmsg, plen)))
        return (NULL);
    free(pmsg);
//    i = -1;
//    while (++i < 4)
//        vars[i] = ft_bswap_uint32((u_int32_t)vars[i]);
    //fprintf(stderr, "vars = %2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx\n",
    //        ((unsigned char*)vars)[0],
    //        ((unsigned char*)vars)[1],
    //        ((unsigned char*)vars)[2],
    //        ((unsigned char*)vars)[3],
    //        ((unsigned char*)vars)[4],
    //        ((unsigned char*)vars)[5],
    //        ((unsigned char*)vars)[6],
    //        ((unsigned char*)vars)[7],
    //        ((unsigned char*)vars)[8],
    //        ((unsigned char*)vars)[9],
    //        ((unsigned char*)vars)[10],
    //        ((unsigned char*)vars)[11],
    //        ((unsigned char*)vars)[12],
    //        ((unsigned char*)vars)[13],
    //        ((unsigned char*)vars)[14],
    //        ((unsigned char*)vars)[15]);
    //if (!(hash = md5_build_hash(vars)))
    //    return (NULL);
    //free(vars);
    return ((unsigned char*)vars);
}
