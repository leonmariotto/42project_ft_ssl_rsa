/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_enckey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:20:01 by leon              #+#    #+#             */
/*   Updated: 2021/12/15 20:17:41 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int				gen_enckey(uint32_t p, uint32_t q, int randomfd)
{
	uint64_t	e;

	if (!get_random(&e, 8, randomfd))
		return (0);
	while (euclide(e, (p - 1) * (q - 1)) != 1)
	{
		if (!get_random(&e, 8, randomfd))
			return (0);
		ft_putchar_fd('.', 2);
	}
	ft_putchar_fd('\n', 2);
	return (e);
}
