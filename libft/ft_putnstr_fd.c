/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:15:23 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:15:24 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(int fd, int n, ...)
{
	va_list	str;

	va_start(str, n);
	while (n--)
		ft_putstr_fd(va_arg(str, char*), fd);
	va_end(str);
}
