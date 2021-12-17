/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:08:15 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 13:43:21 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

const int tkey_permutation[] =
{
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

const int tkey_compression_permutation[] =
{
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int tkey_shifts[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void                tkey_init_permutation(unsigned char *key, t_keyring *ret)
{
    int         i;
    u_int8_t    sb;
    int         sz;

    i = 0;
    while (i < 56)
    {
        sz = tkey_permutation[i];
        sb = 0x80 >> ((sz - 1) % 8);
        sb &= key[(sz - 1) / 8];
        sb <<= ((sz - 1) % 8);
        ret[0].k[i / 8] |= (sb >> i % 8);
        i++;
    }
}

void                tkey_separate(t_keyring *ret)
{
    int i;

    i = 0;
    while (i < 3)
    {
        ret[0].l[i] = ret[0].k[i];
        i++;
    }
    ret[0].l[3] = ret[0].k[3] & 0xF0;
    i = 0;
    while (i < 3)
    {
        ret[0].r[i] = (u_int8_t)((ret[0].k[i + 3] & 0x0F) << 4);
        ret[0].r[i] |= (ret[0].k[i + 4] & 0xF0) >> 4;
        i++;
    }
    ret[0].r[3] = (u_int8_t)((ret[0].k[6] & 0x0F) << 4);
}

void                 tkey_process(int i, t_keyring *ret)
{
    int             j;
    u_int8_t        tmp;
    unsigned char   save;
    int             sz;
    int             sb;

    j = 0;
    while (j < 4)
    {
        ret[i].r[j] = ret[i - 1].r[j];
        ret[i].l[j] = ret[i - 1].l[j];
        j++;
    }
    sz = tkey_shifts[i];
    sb = (sz == 1 ? 0x80 : 0xC0);
    save = sb & ret[i].l[0];
    ret[i].l[0] <<= sz;
    ret[i].l[0] |= ((sb & ret[i].l[1]) >> (8 - sz));
    ret[i].l[1] <<= sz;
    ret[i].l[1] |= ((sb & ret[i].l[2]) >> (8 - sz));
    ret[i].l[2] <<= sz;
    ret[i].l[2] |= ((sb & ret[i].l[3]) >> (8 - sz));
    ret[i].l[3] <<= sz;
    ret[i].l[3] |= (save >> (4 - sz));
    save = sb & ret[i].r[0];
    ret[i].r[0] <<= sz;
    ret[i].r[0] |= ((sb & ret[i].r[1]) >> (8 - sz));
    ret[i].r[1] <<= sz;
    ret[i].r[1] |= ((sb & ret[i].r[2]) >> (8 - sz));
    ret[i].r[2] <<= sz;
    ret[i].r[2] |= ((sb & ret[i].r[3]) >> (8 - sz));
    ret[i].r[3] <<= sz;
    ret[i].r[3] |= (save >> (4 - sz));
    j = 0;
    while (j < 48)
    {
        if (tkey_compression_permutation[j] <= 28)
        {
            tmp = 0x80 >> ((tkey_compression_permutation[j] - 1) % 8);
            tmp &= ret[i].l[(tkey_compression_permutation[j] - 1) / 8];
            tmp <<= ((tkey_compression_permutation[j] - 1) % 8);
        }
        else
        {
            tmp = 0x80 >> ((tkey_compression_permutation[j] - 29) % 8);
            tmp &= ret[i].r[(tkey_compression_permutation[j] - 29) / 8];
            tmp <<= ((tkey_compression_permutation[j] - 29) % 8);
        }
        ret[i].k[j / 8] |= (tmp >> j % 8);
        j++;
    }
}

t_keyring                *tkey(unsigned char *key)
{
    t_keyring   *ret;
    int         i;

    if (!(ret = (t_keyring*)ft_memalloc(sizeof(t_keyring) * 17)))
        return (NULL);
    i = 1;
    tkey_init_permutation(key, ret);
    tkey_separate(ret);
    while (i < 17)
    {
        tkey_process(i++, ret);
    }
    return (ret);
}
