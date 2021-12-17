/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:11:40 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:11:41 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	void *next;

	if (lst == NULL || f == NULL)
		return ;
	next = lst->next;
	f(lst);
	if (next != NULL)
		ft_lstiter(next, f);
}
