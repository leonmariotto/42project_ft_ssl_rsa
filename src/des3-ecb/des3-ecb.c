/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3-ecb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 17:48:18 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 17:43:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int                 des3_ecb_decrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
    char            buf[8];
    char            *result;
    char            *tmp;
    int             nlen;
    t_keyring       *keys[3];

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
        //if (get_des()->opt->pbkdf2)
            pbkdf2(get_des()->opt->passwd, ft_strlen(get_des()->opt->passwd), 
            get_des()->salt, 8, 24, 8, get_des()->opt->iter);
        //else
        //    ossl_pbkdf(get_des()->opt->passwd, get_des()->salt, 8, 8);
        // TODO gen clé avec ossl_pbkdf ?
    }
    else
    {
        if (!get_des()->iv)
            return (0);
    }
    if (!(*ptr = malloc(nlen)))
        return (0);
    keys[0] = tkey(&(get_des()->key[0]));
    keys[1] = tkey(&(get_des()->key[8]));
    keys[2] = tkey(&(get_des()->key[16]));
    while (i < *len)
    {
        ft_memcpy(buf, input + i, 8);
        result = des_blockey(buf, 1, keys[2]);
        tmp = des_blockey(result, 0, keys[1]);
        free(result);
        result = des_blockey(tmp, 1, keys[0]);
        free(tmp);
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
    free(keys[0]);
    free(keys[1]);
    free(keys[2]);
    *len = nlen;
    return (1);
}

int                 des3_ecb_encrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
    char            buf[8];
    char            *result;
    char            *tmp;
    int             nlen;
    t_keyring       *keys[3];

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
        //if (get_des()->opt->pbkdf2)
            pbkdf2(get_des()->opt->passwd, ft_strlen(get_des()->opt->passwd), 
            get_des()->salt, 8, 24, 8, get_des()->opt->iter);
        //else
        //    ossl_pbkdf(get_des()->opt->passwd, get_des()->salt, 8, 8);
        // TODO gen clé avec ossl_pbkdf ?
    }
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
    keys[0] = tkey(&(get_des()->key[0]));
    keys[1] = tkey(&(get_des()->key[8]));
    keys[2] = tkey(&(get_des()->key[16]));
    while (i <= *len)
    {
        if (*len - i < 8)
            ft_memset(buf, (*len - i != 0 ? 8 - (*len - i) : 8), 8);
        ft_memcpy(buf, input + i, (*len - i < 8 ? *len - i : 8));
        result = des_blockey(buf, 0, keys[0]);
        tmp = des_blockey(result, 1, keys[1]);
        free(result);
        result = des_blockey(tmp, 0, keys[2]);
        free(tmp);
        ft_memcpy(*ptr + (get_des()->salt ? i + 16 : i), result, 8);
        free(result);
        i += 8;
    }
    free(keys[0]);
    free(keys[1]);
    free(keys[2]);
    *len = nlen;
    return (1);
}

int                 des3_ecb(void **ptr, const unsigned char *input, int *len, char mod)
{
    int     r;

    if (!mod)
    {
        r = des3_ecb_encrypt(ptr, input, len);
    }
    else
    {
        r = des3_ecb_decrypt(ptr, input, len);
    }
    return (r);
}

