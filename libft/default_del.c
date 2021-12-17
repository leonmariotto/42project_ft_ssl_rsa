/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:06:52 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:06:53 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	default_del(void *content, size_t content_size)
{
	free((void *)content);
	(void)content_size;
}
