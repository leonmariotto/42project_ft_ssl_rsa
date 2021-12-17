/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:12:18 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:12:19 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **lst)
{
	t_list *l;

	if (!lst)
		return ;
	l = NULL;
	while (*lst)
	{
		ft_lstadd(&l, *lst);
		*lst = (*lst)->next;
	}
	*lst = l;
}
