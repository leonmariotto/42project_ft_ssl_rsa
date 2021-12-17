/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ossl_pbkdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 12:48:32 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/24 20:19:45 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

#include "sha256.h"
#include <stdio.h>

void            *hasher(char *temp, char *passwd, char *salt)
{
    char *buf;
    char *ptr;
    void *ret;

    if (!(buf = ft_memalloc(40 + ft_strlen(passwd))))
        return (NULL);
    ft_bzero(buf, 40 + ft_strlen(passwd));
    ptr = buf;
    if (temp)
    {
        ft_memcpy(ptr, temp, 32);
        ptr += 32;
    }
    ft_memcpy(ptr, passwd, ft_strlen(passwd));
    ptr += ft_strlen(passwd);
    ft_memcpy(ptr, salt, 8);
    if (temp)
        ret = (void*)sha256(buf, 40 + ft_strlen(passwd));
    else
        ret = (void*)sha256(buf, 8 + ft_strlen(passwd));
    free(buf);
    return (ret);
}

u_int8_t        *ossl_pbkdf(char *passwd, u_int8_t *salt,
                            size_t key_size, size_t iv_size)
{
    char    *buffer;
    char    *temp;
    size_t     len;

    if (!(buffer = (char*)ft_memalloc(key_size + iv_size)))
        return (NULL);
    len = 0;
    temp = NULL;
    while (len < key_size + iv_size)
    {
        temp = hasher(temp, passwd, (char*)salt);
        ft_memcpy(buffer + len, temp, (len + 32 > key_size + iv_size ?
                                    (key_size + iv_size) - len : 32));
        free(temp);
        len += 32;
    }
    if (!(get_des()->key = ft_memalloc(key_size)))
        return (NULL);
    ft_memcpy(get_des()->key, buffer, key_size);
    if (!get_des()->iv)
    {
        if (!(get_des()->iv = ft_memalloc(iv_size)))
            return (NULL);
        ft_memcpy(get_des()->iv, buffer + key_size, iv_size);
    }
    free(buffer);
    return (NULL);
}
