/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_by_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:22:08 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 13:21:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

int         sha256_by_fd(int fd)
{
    char        *msg;
    long int        len;
    unsigned char        *hash;

    msg = NULL;
    if ((len = ft_readfd(fd, &msg)) <= 0)
        return (0);
    if (get_sha256()->opt->p && !fd)
        write(1, msg, len);
    if (!(hash = sha256(msg, len)))
        return (0);
    ft_puthexlen(hash, 32);
    free(hash);
    free(msg);
    return (1);
}
