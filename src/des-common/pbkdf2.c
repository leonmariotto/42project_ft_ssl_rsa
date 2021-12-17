/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:36:03 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:34:43 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "sha256.h"
#include <stdio.h>

# define SHA256_BLOCK_LENGHT 64
# define SHA256_DIGEST_LENGHT 32

// Pointeur de clé et iv en parametre ?

int            hmac_sha256(u_int8_t *asalt, size_t asalt_len, 
                                u_int8_t *pswd, size_t pswd_len,
                                u_int8_t res[SHA256_DIGEST_LENGHT])
{
    unsigned int        i;
    u_int8_t            *tmp;
    u_int8_t            cat[SHA256_BLOCK_LENGHT + 
(asalt_len > SHA256_BLOCK_LENGHT ? asalt_len : SHA256_BLOCK_LENGHT)];
    u_int8_t            *key;
    size_t              key_len;
    u_int8_t            k_pad[SHA256_BLOCK_LENGHT];
    
    if (!(key = ft_memdup((void*)pswd, pswd_len)))
        return (0);
    key_len = pswd_len;
    if (key_len > SHA256_BLOCK_LENGHT) 
    {
        free(key);
        key = sha256((char*)pswd, pswd_len);
        key_len = SHA256_DIGEST_LENGHT;
    }
    ft_bzero(k_pad, SHA256_BLOCK_LENGHT);
    ft_memcpy(k_pad, key, key_len);
    i = 0;
    while (i < SHA256_BLOCK_LENGHT)
        k_pad[i++] ^= 0x36;
    ft_memcpy(cat, k_pad, SHA256_BLOCK_LENGHT);
    ft_memcpy(cat + SHA256_BLOCK_LENGHT, asalt, asalt_len);
    tmp = sha256((char*)cat, SHA256_BLOCK_LENGHT + asalt_len);
    ft_bzero(k_pad, SHA256_BLOCK_LENGHT);
    ft_memcpy(k_pad, key, key_len);
    i = 0;
    while (i < SHA256_BLOCK_LENGHT)
        k_pad[i++] ^= 0x5c;
    ft_memcpy(cat, k_pad, SHA256_BLOCK_LENGHT);
    ft_memcpy(cat + SHA256_BLOCK_LENGHT, tmp, SHA256_DIGEST_LENGHT);
    free(tmp);
    tmp = sha256((char*)cat, SHA256_BLOCK_LENGHT + SHA256_DIGEST_LENGHT);
    ft_memcpy(res, tmp, SHA256_DIGEST_LENGHT);
    free(key);
    free(tmp);
    return (1);
}

int         pbkdf2(char *passwd, size_t pass_len,
                        u_int8_t *salt, size_t salt_len,
                            size_t key_size, size_t iv_size,
                            unsigned int round)
{
    unsigned int    i;
    unsigned int    j;
    int             k;
    unsigned int    c;
    u_int8_t         *asalt;
    u_int8_t         d1[SHA256_DIGEST_LENGHT];
    u_int8_t         d2[SHA256_DIGEST_LENGHT];
    u_int8_t         obuf[SHA256_DIGEST_LENGHT];
    u_int8_t         *buffer;

    i = 0;
    c = 1;
    if (!(asalt = ft_memalloc(salt_len + 4)))
        return (0);
    ft_memcpy(asalt, salt, salt_len);
    if (!(buffer = ft_memalloc(key_size + iv_size)))
        return (0);
    while (i < key_size + iv_size)
    {
        asalt[salt_len + 0] = (c >> 24) & 0xff;
        asalt[salt_len + 1] = (c >> 16) & 0xff;
        asalt[salt_len + 2] = (c >> 8) & 0xff;
        asalt[salt_len + 3] = c & 0xff; 
        hmac_sha256(asalt, salt_len + 4, (unsigned char *)passwd, pass_len, d1);
        ft_memcpy(obuf, d1, SHA256_DIGEST_LENGHT);
        j = 1;
        while (j < round)
        {
            hmac_sha256(d1, SHA256_DIGEST_LENGHT, (u_int8_t*)passwd, pass_len, d2);
            ft_memcpy(d1, d2, SHA256_DIGEST_LENGHT);
            k = -1;
            while (++k < SHA256_DIGEST_LENGHT)
                obuf[k] ^= d1[k];
            j++;
        }
        ft_memcpy(buffer + i, obuf, ((key_size + iv_size) - i <
        SHA256_DIGEST_LENGHT ? (key_size + iv_size) - i : SHA256_DIGEST_LENGHT));
        i += ((key_size + iv_size) - i <
        SHA256_DIGEST_LENGHT ? (key_size + iv_size) - i : SHA256_DIGEST_LENGHT);
        c++;
    }
    free(asalt);
    if (!(get_des()->key = ft_memalloc(key_size)))
        return (0);
    ft_memcpy(get_des()->key, buffer, key_size);
    if (!(get_des()->iv = ft_memalloc(iv_size)))
        return (0);
    ft_memcpy(get_des()->iv, buffer + key_size, iv_size);
    free(buffer);
    return (1);
}
