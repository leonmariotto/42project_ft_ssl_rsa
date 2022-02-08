/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:36:32 by lmariott          #+#    #+#             */
/*   Updated: 2022/02/08 20:48:34 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int			parse_pem(char **input, bool pub, int *len)
{
	char		*new;
	int		i;
	int		j;

	j = 0;
	if (!pub)
	{
		if (ft_memcmp(*input, "-----BEGIN RSA PRIVATE KEY-----\n", 32))
			return (0);
		if (!(new = malloc(*len - 60)))
			return (0);
		i = 32;
		while (i < *len - 30)
		{
			if ((*input)[i] != '\n' && (*input)[i] != ' ')
				new[j++] = (*input)[i];
			i++;
		}
		new[j] = 0;
	}
	if (pub)
	{
		if (ft_strncmp(*input, "-----BEGIN PUBLIC KEY-----\n", 27))
			return (0);
		i = 27;
		if (!(new = malloc(*len - 48)))
			return (0);
		while (i < *len - 25)
		{
			if ((*input)[i] != '\n' && (*input)[i] != ' ')
				new[j++] = (*input)[i];
			i++;
		}
		new[j] = 0;
	}
	free(*input);
	*input = new;
	*len = j;
	return (1);
}
