/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:18:16 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 12:05:13 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void        ft_puthexlen(unsigned char *bin, int len)
{
    int     i;
    char   *tmp;

    i = -1;
    while (++i < len)
    {
        tmp = ft_ui8toa_base_len(bin[i], 16, 2);
        ft_putstr(tmp);
        free(tmp);
    }
}
