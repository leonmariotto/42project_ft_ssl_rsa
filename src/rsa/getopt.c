/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:11:24 by leon              #+#    #+#             */
/*   Updated: 2021/12/14 17:49:07 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			rsa_getopt(t_rsa_opt *opt, void **av, int ac)
{
	int i;

	i = 1;
	(*opt).outfd = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-inform"))
		{
			i++;
			if (ft_strcmp(av[i], "PEM"))
			{
				ft_putendl_fd("Error, only support for PEM...", 2);
				return (0);
			}
		}
		else if (!ft_strcmp(av[i], "-outform"))
		{
			i++;
			if (ft_strcmp(av[i], "PEM"))
			{
				ft_putendl_fd("Error, only support for PEM...", 2);
				return (0);
			}
		}
		else if (!ft_strcmp(av[i], "-in"))
		{
			i++;
			if (((*opt).infd = open(av[i], O_RDONLY)) < 0)
				return (0);
		}
		else if (!ft_strcmp(av[i], "-out"))
		{
			i++;
			if (((*opt).outfd = open(av[i], O_CREAT |
					O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
				return (0);
		}
		else if (!ft_strcmp(av[i], "-passin"))
		{
			i++;
			(*opt).passin = av[i];
		}
		else if (!ft_strcmp(av[i], "-passout"))
		{
			i++;
			(*opt).passout = av[i];
		}
		else if (!ft_strcmp(av[i], "-des"))
			(*opt).des_cbc = 1;
		else if (!ft_strcmp(av[i], "-des-cbc"))
			(*opt).des_cbc = 1;
		else if (!ft_strcmp(av[i], "-des-ecb"))
			(*opt).des_ecb = 1;
		else if (!ft_strcmp(av[i], "-text"))
			(*opt).text = 1;
		else if (!ft_strcmp(av[i], "-noout"))
			(*opt).noout = 1;
		else if (!ft_strcmp(av[i], "-modulus"))
			(*opt).modulus = 1;
		else if (!ft_strcmp(av[i], "-check"))
			(*opt).check = 1;
		else if (!ft_strcmp(av[i], "-pubin"))
			(*opt).pubin = 1;
		else if (!ft_strcmp(av[i], "-pubout"))
			(*opt).pubout = 1;
	}
	return (1);
}
