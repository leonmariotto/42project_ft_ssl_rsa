/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:15:16 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:15:17 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(int n, ...)
{
	va_list	str;

	va_start(str, n);
	while (n--)
		ft_putstr(va_arg(str, char*));
	va_end(str);
}
