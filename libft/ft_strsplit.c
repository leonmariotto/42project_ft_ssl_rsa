/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:04:37 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 14:04:39 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (*s && *s != c)
			if (*(s + 1) == c || !(*(s + 1)))
				i++;
		s++;
	}
	return (i);
}

static int	count_letters(const char *s, char c)
{
	int		i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static char	**free_split(char **split, int stop)
{
	int		i;

	i = 0;
	while (i < stop)
	{
		ft_strdel(split + i);
		i++;
	}
	free(split);
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	if (!(split = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			j = count_letters(s, c);
			if (!(*(split + i) = ft_strsub(s, 0, j)))
				return (free_split(split, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	*(split + i) = NULL;
	return (split);
}
