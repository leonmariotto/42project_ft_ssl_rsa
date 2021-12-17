/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:42:27 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/13 09:51:56 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

int         sha256_exit(void)
{
    t_sha256    *sha256;

    sha256 = get_sha256();
    ft_lstdel(&sha256->opt->str, default_del);
    ft_lstdel(&sha256->opt->files, default_del);
    free(sha256->opt);
    free(sha256);
    return (0);
}
