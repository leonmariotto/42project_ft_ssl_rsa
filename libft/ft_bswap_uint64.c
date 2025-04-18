/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap_uint64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 08:55:00 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/13 08:58:23 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

u_int64_t	ft_bswap_uint64(u_int64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL)
		| ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL)
		| ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return (x << 32) | (x >> 32);
}
