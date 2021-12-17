/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:41:32 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/13 17:37:56 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int                 des_ecb_decrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
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
        //free(get_des()->key);
        //if (!get_des()->opt->v)
        //{
        //    free(get_des()->iv);
        //    get_des()->iv = NULL;
        //}
        //if (!get_key())
        //    return (0);
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

int                 des_ecb_encrypt(void **ptr, const unsigned char *input, int *len)
{
    int             i;
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
        //printf("key: [%02x%02x%02x%02x%02x%02x%02x%02x]\n",
        //        get_des()->key[0],
        //        get_des()->key[1],
        //        get_des()->key[2],
        //        get_des()->key[3],
        //        get_des()->key[4],
        //        get_des()->key[5],
        //        get_des()->key[6],
        //        get_des()->key[7]);
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
    if (!(get_des()->keyring = tkey(get_des()->key)))
        return (0);
    while (i <= *len)
    {
        if (*len - i < 8)
            ft_memset(buf, (*len - i != 0 ? 8 - (*len - i) : 8), 8);
        ft_memcpy(buf, input + i, (*len - i < 8 ? *len - i : 8));
        result = des_blockey(buf, 0, get_des()->keyring);
        ft_memcpy(*ptr + (get_des()->salt ? i + 16 : i), result, 8);
        free(result);
        i += 8;
    }
    *len = nlen;
    return (1);
}

int                 des_ecb(void **ptr, const unsigned char *input, int *len, char mod)
{
    int     r;

    //if (!get_des()->key)
    //    return (0);
    if (!mod)
    {
        r = des_ecb_encrypt(ptr, input, len);
    }
    else
    {
        r = des_ecb_decrypt(ptr, input, len);
    }
    return (r);
}

//int             des_ecb(void **av, int ac)
//{
//    t_des       *des;
//
//    des = get_des();
//    if (!des_get_opt((char **)av, ac))
//    {
//        free(get_des()->opt);
//        free(get_des());
//        return (0);
//    }
//    if (!get_des()->key)
//    {
//        if (!get_key())
//            return (0);
//    }
//    if (!des->opt->d)
//        des_ecb_encrypt();
//    else
//        des_ecb_decrypt();
//    close(des->opt->output);
//    close(des->opt->input);
//    return (0);
//}

    // DEBUG
    //if (des->opt->passwd && des->salt)
    //{
    //    printf("password: [%s]\n", des->opt->passwd);
    //    printf("salt: [%02x%02x%02x%02x%02x%02x%02x%02x]\n",
    //            des->salt[0],
    //            des->salt[1],
    //            des->salt[2],
    //            des->salt[3],
    //            des->salt[4],
    //            des->salt[5],
    //            des->salt[6],
    //            des->salt[7]);
    //}
    //printf("key: [%02x%02x%02x%02x%02x%02x%02x%02x]\n",
    //        des->key[0],
    //        des->key[1],
    //        des->key[2],
    //        des->key[3],
    //        des->key[4],
    //        des->key[5],
    //        des->key[6],
    //        des->key[7]);
    // END DEBUG
