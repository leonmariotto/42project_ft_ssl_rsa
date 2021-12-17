/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:37:08 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/19 11:38:20 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int         md5_exit(void)
{
    t_md5    *md5;

    md5 = get_md5();
    ft_lstdel(&md5->opt->str, default_del);
    ft_lstdel(&md5->opt->files, default_del);
    free(md5->opt);
    free(md5);
    return (0);
}
