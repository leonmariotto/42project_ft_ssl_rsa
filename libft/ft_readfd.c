/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:59:55 by lmariott          #+#    #+#             */
/*   Updated: 2021/10/20 16:21:22 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <errno.h>

int        ft_readfd(int fd, char **msg)
{
    int             r;
    u_int64_t       len;
    char            buf[2048];
    char            *tmp;

    len = 0;
    *msg = NULL;
    while ((r = read(fd, buf, 2048)) > 0)
    {
        if (!(tmp = (char*)malloc(len + r)))
            return (0);
        ft_memcpy(tmp, *msg, len);
        ft_memcpy(tmp + len, buf, r);
        if (*msg)
            free(*msg);
        len += r;
        *msg = tmp;
    }
    if (r < 0)
    {
//        perror("read");
        ft_putendl_fd("error: ft_readfd", 2);
        return (-1);
    }
    //msg[len] = '\0';
    return (len);
}
