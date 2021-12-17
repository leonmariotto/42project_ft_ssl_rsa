/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 09:59:43 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:29:14 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

t_des           *get_des(void)
{
    static t_des        *sdes = NULL;

    if (sdes)
        return (sdes);
    if (!(sdes = (t_des*)ft_memalloc(sizeof(t_des))))
        return (NULL);
    if (!(sdes->opt = (t_desopt*)ft_memalloc(sizeof(t_desopt))))
    {
        free(sdes);
        return (NULL);
    }
    sdes->iv = NULL;
    sdes->opt->input = 0;
    sdes->opt->output = 1;
    sdes->opt->pbkdf2 = 0;
    sdes->opt->iter = 10;
    return (sdes);
}
