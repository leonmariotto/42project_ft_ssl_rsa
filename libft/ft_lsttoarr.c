/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:04:20 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:04:22 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_lsttoarr(t_list *lst)
{
	char	**arr;
	int		i;

	if (!lst)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1))))
		return (NULL);
	i = 0;
	while (lst && lst->content)
	{
		if (!(arr[i++] = ft_strdup((char *)lst->content)))
		{
			arr[i] = NULL;
			ft_arrfree((void**)arr);
			return (NULL);
		}
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}
