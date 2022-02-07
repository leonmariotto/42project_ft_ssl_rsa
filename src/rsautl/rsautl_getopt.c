/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_getopt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:16:58 by leon              #+#    #+#             */
/*   Updated: 2022/01/12 19:17:25 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			rsautl_getopt(t_rsautl_opt *opt, char **av, int ac)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-in"))
		{
			++i;
			if (((*opt).infd = open(av[i], O_RDONLY)) < 0)
				return (0);
		}
		else if (!ft_strcmp(av[i], "-out"))
		{
			++i;
			if (((*opt).outfd = open(av[i], O_CREAT |
					O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
				return (0);
		}
		else if (!ft_strcmp(av[i], "-inkey"))
		{
			++i;
			if (((*opt).keyfd = open(av[i], O_RDONLY)) < 0)
				return (0);
		}
		else if (!ft_strcmp(av[i], "-pass"))
		{
			i++;
			(*opt).pass = av[i];
		}
		else if (!ft_strcmp(av[i], "-pubin"))
			(*opt).pubin = 1;
		else if (!ft_strcmp(av[i], "-encrypt"))
			(*opt).decrypt = 0;
		else if (!ft_strcmp(av[i], "-decrypt"))
			(*opt).decrypt = 1;
		else if (!ft_strcmp(av[i], "-d"))
			(*opt).decrypt = 1;
		else if (!ft_strcmp(av[i], "-hexdump"))
			(*opt).hexdump = 1;
		else
			return (err_return("unknow opt\n"));
	}
	return (1);
}
