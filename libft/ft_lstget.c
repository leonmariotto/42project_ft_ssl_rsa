/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:11:34 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:11:35 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *lst, const size_t index)
{
	size_t i;

	i = 0;
	while (lst && i < index)
	{
		++i;
		lst = lst->next;
	}
	return (lst);
}
