/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:06:48 by lmariott          #+#    #+#             */
/*   Updated: 2021/07/26 11:45:28 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static void            init_const(t_base64 *base64)
{
    base64->opt->d = 0;
    base64->opt->input = 0;
    base64->opt->output = 1;
}

t_base64        *get_base64(void)
{
    static t_base64    *c_base64 = NULL;

    if (c_base64)
        return (c_base64);
    if (!(c_base64 = (t_base64*)ft_memalloc(sizeof(t_base64))))
        return (NULL);
    if (!(c_base64->opt = (t_base64opt*)ft_memalloc(sizeof(t_base64opt))))
    {
        free(c_base64);
        return (NULL);
    }
    init_const(c_base64);
    return (c_base64);
}
