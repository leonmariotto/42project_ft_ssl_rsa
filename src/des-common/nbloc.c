/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_blockey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:31:04 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:27:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "consts_des.h"

// TODO optimize
// remove all malloc

char                *blockey_msg_exp(int i, char *buf, t_keyring *keys, char r_exp[6])
{
    char        r[8];
    char        l[8];
    //char        *r_exp;
    int         j;
    u_int8_t    tmp;

    j = 0;
    ft_memcpy(l, buf, 4);
    ft_memcpy(r, buf + 4, 4);
    //if (!(r_exp = (char*)ft_memalloc(6)))
    //    return (NULL);
    while (j < 48)
    {
        tmp = 0x80 >> ((msg_expansion_permutation[j] - 1) % 8);
        tmp &= r[(msg_expansion_permutation[j] - 1) / 8];
        tmp <<= ((msg_expansion_permutation[j] - 1) % 8);
        r_exp[j / 8] |= (tmp >> j % 8);
        j++;
    }
    j = 0;
    while (j < 6)
    {
        r_exp[j] ^= keys[i].k[j];
        j++;
    }
    //return (r_exp);
    return (1);
}

char                *blockey_msg_shift_exp(char r_exp[6], char ser[4])
{
    int     column;
    int     row;
    //char    *ser;

    //if (!(ser = (char*)ft_memalloc(4)))
    //    return (NULL);
    row = 0;
    row |= ((r_exp[0] & 0x80) >> 6);
    row |= ((r_exp[0] & 0x04) >> 2);
    column = 0;
    column |= ((r_exp[0] & 0x78) >> 3);
    ser[0] |= ((unsigned char)S1[row*16+column] << 4);
    row = 0;
    row |= (r_exp[0] & 0x02);
    row |= ((r_exp[1] & 0x10) >> 4);
    column = 0;
    column |= ((r_exp[0] & 0x01) << 3);
    column |= ((r_exp[1] & 0xE0) >> 5);
    ser[0] |= (unsigned char)S2[row*16+column];
    row = 0;
    row |= ((r_exp[1] & 0x08) >> 2);
    row |= ((r_exp[2] & 0x40) >> 6);
    column = 0;
    column |= ((r_exp[1] & 0x07) << 1);
    column |= ((r_exp[2] & 0x80) >> 7);
    ser[1] |= ((unsigned char)S3[row*16+column] << 4);
    row = 0;
    row |= ((r_exp[2] & 0x20) >> 4);
    row |= (r_exp[2] & 0x01);
    column = 0;
    column |= ((r_exp[2] & 0x1E) >> 1);
    ser[1] |= (unsigned char)S4[row*16+column];
    row = 0;
    row |= ((r_exp[3] & 0x80) >> 6);
    row |= ((r_exp[3] & 0x04) >> 2);
    column = 0;
    column |= ((r_exp[3] & 0x78) >> 3);
    ser[2] |= ((unsigned char)S5[row*16+column] << 4);
    row = 0;
    row |= (r_exp[3] & 0x02);
    row |= ((r_exp[4] & 0x10) >> 4);
    column = 0;
    column |= ((r_exp[3] & 0x01) << 3);
    column |= ((r_exp[4] & 0xE0) >> 5);
    ser[2] |= (unsigned char)S6[row*16+column];
    row = 0;
    row |= ((r_exp[4] & 0x08) >> 2);
    row |= ((r_exp[5] & 0x40) >> 6);
    column = 0;
    column |= ((r_exp[4] & 0x07) << 1);
    column |= ((r_exp[5] & 0x80) >> 7);
    ser[3] |= ((unsigned char)S7[row*16+column] << 4);
    row = 0;
    row |= ((r_exp[5] & 0x20) >> 4);
    row |= (r_exp[5] & 0x01);
    column = 0;
    column |= ((r_exp[5] & 0x1E) >> 1);
    ser[3] |= (unsigned char)S8[row*16+column];
    //return (ser);
    return (1);
}

char                *blockey_rpbox(char ser[4], char rpox[4])
{
    //char        *r_pbox;
    int         i;
    u_int8_t    tmp;

    //if (!(r_pbox = (char*)ft_memalloc(4)))
    //    return (NULL);
    i = 0;
    while (i < 32)
    {
        tmp = 0x80 >> ((msg_right_pbox[i] - 1) % 8);
        tmp &= ser[(msg_right_pbox[i] - 1) / 8];
        tmp <<= ((msg_right_pbox[i] - 1) % 8);
        r_pbox[i / 8] |= (tmp >> i % 8);
        i++;
    }
    //return (r_pbox);
    return (1);
}

int                 des_blockey_pass(int i, char *buf, t_keyring *keys)
{
    //char        *r_exp;
    //char        *shift_r_exp;
    //char        *r_pbox;
    char        r_exp[6];
    char        shift_r_exp[4];
    char        r_pbox[4];
    int         j;
    char        pre_end[8];
    char        ln[4];

    ft_memcpy(ln, buf + 4, 4);
    if (!blockey_msg_exp(i, buf, keys, r_exp) || // [6]
        !blockey_msg_shift_exp(r_exp, shift_r_exp) || // [4]
        !blockey_rpbox(shift_r_exp, r_pbox)) // [4]
        return (0);
    j = 0;
    while (j < 4)
    {
        r_pbox[j] ^= buf[j];
        pre_end[j] = ln[j];
        pre_end[j + 4] = r_pbox[j];
        j++;
    }
    ft_memcpy(buf, pre_end, 8);
    free(r_exp);
    free(shift_r_exp);
    free(r_pbox);
    return (1);
}

char            *blockey_final_permutation(char *buf)
{
    int     i;
    char    *final;
    u_int8_t    tmp;
    char        pre_end[8];

    ft_memcpy(pre_end, buf + 4, 4);
    ft_memcpy(pre_end + 4, buf, 4);
    if (!(final = (char*)ft_memalloc(8)))
        return (NULL);
    i = 0;
    while (i < 64)
    {
        tmp = 0x80 >> ((msg_final_permutation[i] - 1) % 8);
        tmp &= pre_end[(msg_final_permutation[i] - 1) / 8];
        tmp <<= ((msg_final_permutation[i] - 1) % 8);
        final[i / 8] |= (tmp >> i % 8);
        i++;
    }
    return (final);
}

void                    blockey_init_permutation(unsigned char *buf)
{
    int         i;
    u_int8_t    tmp;
    unsigned char        bufp[8];

    i = 0;
    ft_bzero(bufp, 8);
    while (i < 64)
    {
        tmp = 0x80 >> ((initial_msg_permutation[i] - 1) % 8);
        tmp &= buf[(initial_msg_permutation[i] - 1) / 8];
        tmp <<= ((initial_msg_permutation[i] - 1) % 8);
        bufp[i / 8] |= (tmp >> i % 8);
        i++;
    }
    ft_memcpy(buf, bufp, 8);
}

char                    *des_blockey(char *buf, char mod, t_keyring *keys)
{
    int         i;
    char        *result;

    blockey_init_permutation((unsigned char*)buf);
    if (!mod)
    {
        i = 1;
        while (i < 17)
        {
            if (!des_blockey_pass(i++, buf, keys))
                return (0);
        }
    }
    else
    {
        i = 16;
        while (i > 0)
        {
            if (!des_blockey_pass(i--, buf, keys))
                return (0);
        }
    }
    result = blockey_final_permutation(buf);
    return (result);
}
