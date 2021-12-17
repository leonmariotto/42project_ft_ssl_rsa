/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:06:40 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:26:09 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int             des_cbc_decrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
    int             j;
    char            buf[8];
    char            *result;
    int             nlen;

    i = 0;
    nlen = *len;
    if (!ft_memcmp(input, "Salted__", 8))
    {
        if (!get_des()->salt)
        {
            if (!(get_des()->salt = ft_memalloc(8)))
                return (0);
        }
        ft_memcpy(get_des()->salt, input + 8, 8);
        nlen -= 16;
        i += 16;
    }
    else
    {
        if (!(gen_salt(&get_des()->salt)))
            return (0);
    }
    if (!get_des()->key)
    {
        if (!get_des()->opt->passwd)
        {
            if (!(ask_paswd(&get_des()->opt->passwd)))
                return (0);
        }
        if (get_des()->opt->pbkdf2)
            pbkdf2(get_des()->opt->passwd, ft_strlen(get_des()->opt->passwd), 
            get_des()->salt, 8, 8, 8, get_des()->opt->iter);
        else
            ossl_pbkdf(get_des()->opt->passwd, get_des()->salt, 8, 8);
    }
    if (!(get_des()->keyring = tkey(get_des()->key)))
        return (0);
    if (!(*ptr = ft_memalloc(nlen)))
        return (0);
    while (i < *len)
    {
        ft_memcpy(buf, input + i, 8);
        result = des_blockey(buf, 1, get_des()->keyring);
        j = -1;
        while (++j < 8)
            result[j] ^= ((nlen == *len ? i == 0 : i == 16) ?
                            get_des()->iv[j] : input[(i - 8) + j]);
        if (*len <= i + 8)
        {
            if (result[7] > 8 || result[7] < 0)
            {
                nlen -= 8;
                free(result);
                break;
            }
            ft_memcpy(*ptr + (nlen != *len ? i - 16 : i), result, 8 - result[7]);
            nlen -= result[7];
        }
        else
            ft_memcpy(*ptr + (nlen != *len ? i - 16 : i), result, 8);
        i += 8;
        free(result);
    }
    *len = nlen;
    return (1);
}

int             des_cbc_encrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
    int             j;
    char            buf[8];
    char            *result;
    int             nlen;


    nlen = (*len % 8 == 0 ? *len + 8 : *len + (8 - *len % 8));
    if (!get_des()->key)
    {
        if (!get_des()->salt)
        {
            if (!(gen_salt(&get_des()->salt)))
                return (0);
        }
        if (!get_des()->opt->passwd)
        {
            if (!(ask_paswd(&get_des()->opt->passwd)))
                return (0);
        }
        if (get_des()->opt->pbkdf2)
            pbkdf2(get_des()->opt->passwd, ft_strlen(get_des()->opt->passwd), 
            get_des()->salt, 8, 8, 8, get_des()->opt->iter);
        else
            ossl_pbkdf(get_des()->opt->passwd, get_des()->salt, 8, 8);
    }
    else
    {
        if (!(get_des()->iv))
            return (0);
    }
    if (!(get_des()->keyring = tkey(get_des()->key)))
        return (0);
    if (get_des()->salt)
        nlen += 16;
    if (!(*ptr = malloc(nlen)))
        return (0);
    if (get_des()->salt)
    {
        ft_memcpy(*ptr, "Salted__", 8);
        ft_memcpy(*ptr + 8, get_des()->salt, 8);
    }
    i = 0;
    result = ft_memdup((char*)get_des()->iv, 8);
    while (i <= *len)
    {
        if (*len - i < 8)
            ft_memset(buf, (*len - i != 0 ? 8 - (*len - i) : 8), 8);
        ft_memcpy(buf, input + i, (*len - i < 8 ? *len - i : 8));
        j = -1;
        while (++j < 8)
            buf[j] ^= result[j];
        free(result);
        result = des_blockey(buf, 0, get_des()->keyring);
        ft_memcpy(*ptr + (get_des()->salt ? i + 16 : i), result, 8);
        i += 8;
    }
    free(result);
    *len = nlen;
    return (1);
}

int             des_cbc(void **ptr, const unsigned char *input, int *len, char mod)
{
    int     r;

    if (!mod)
        r = des_cbc_encrypt(ptr, input, len);
    else
        r = des_cbc_decrypt(ptr, input, len);
    return (r);
}
