/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sha256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:56:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/07 18:43:55 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

t_sha256            *get_sha256(void)
{
    static t_sha256     *sha256 = NULL;

    if (sha256)
        return (sha256);
    if (!(sha256 = (t_sha256*)ft_memalloc(sizeof(t_sha256))))
        return (NULL);
    if (!(sha256->opt = (t_opt*)ft_memalloc(sizeof(t_opt))))
        return (NULL);
    return (sha256);
}
