/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_lendian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:40:21 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/03 09:12:18 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int             ft_is_lendian(void)
{
    unsigned int i;
    char *c;

    i = 1;
    c = (char*)&i;
    if (*c)
        return (1);
    else
        return (0);
}
