/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:36:42 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/07 17:46:55 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_md5           *get_md5(void)
{
    static t_md5    *c_md5 = NULL;

    if (c_md5)
        return (c_md5);
    if (!(c_md5 = (t_md5*)ft_memalloc(sizeof(t_md5))))
        return (NULL);
    if (!(c_md5->opt = (t_opt*)ft_memalloc(sizeof(t_opt))))
    {
        free(c_md5);
        return (NULL);
    }
    return (c_md5);
}
