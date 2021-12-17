/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:11:28 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:11:29 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list *l;

	if (!alst || !(*alst) || !del)
		return ;
	l = (*alst)->next;
	del((*alst)->content, (*alst)->content_size);
	free((void*)*alst);
	*alst = l;
}
