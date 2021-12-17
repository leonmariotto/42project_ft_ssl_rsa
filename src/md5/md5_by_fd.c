/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_by_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 11:27:26 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 13:21:32 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int         md5_by_fd(int fd)
{
    char            *msg;
    long int       len;
    unsigned char            *result;

    msg = NULL;
    if ((len = ft_readfd(fd, &msg)) <= 0)
        return (0);
    if (get_md5()->opt->p && !fd)
    {
        write(1, msg, len);
    }
    if (!(result = md5(msg, len)))
        return (0);
    ft_puthexlen(result, 16);
    free(result);
    free(msg);
    return (1);
}
