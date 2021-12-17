/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:11:46 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:11:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	void	*next;
	t_list	*list;

	if (lst == NULL || f == NULL)
		return (NULL);
	next = lst->next;
	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (0);
	ft_memcpy(list, f(lst), sizeof(t_list));
	if (next != 0)
		list->next = ft_lstmap(next, f);
	return (list);
}
