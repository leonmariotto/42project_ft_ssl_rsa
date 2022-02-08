/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u8hex_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:46:27 by leon              #+#    #+#             */
/*   Updated: 2022/02/08 20:37:17 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void			ft_putu8_hex_fd(uint8_t n, int fd)
{
	char base[16];

	ft_memcpy(base, "0123456789abcdef", 16);
	ft_putchar_fd(base[(n / 16)], fd);
	ft_putchar_fd(base[(n % 16)], fd);
}

