/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rsautl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:18:36 by leon              #+#    #+#             */
/*   Updated: 2021/12/17 11:03:56 by lmariott         ###   ########.fr       */
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
void			ft_putu8_hex_fd(uint8_t n, int fd)
{
	char base[16];

	ft_memcpy(base, "0123456789abcdef", 16);
	if (n > 9)
		ft_putu8_hex_fd(n / 10, fd);
	ft_putchar_fd(base[(n % 10)], fd);
}

int			run_rsautl(char **av, int ac)
{
	t_rsautl_opt	opt;
	t_rsa_key	key;
	char		*input;
	char		buf[8];
	int		len;
	uint64_t	out;
	int		i;
	int		l;

	ft_bzero(&opt, sizeof(opt));
	if (!(rsautl_getopt(&opt, av, ac)))
		return (0);
	if (!opt.keyfd)
		return (err_return("rsautl: You have to specify a key\n"));
	if (!(len = ft_readfd(opt.keyfd, &input)))
		return (err_return("rsautl: unable to read key file\n"));
	//if (!(rsa_extract_key(&input, &len, opt.pubin, opt.pass, &key)))
	//	return (0);
	free(input);
	ft_bzero(buf, 8);
	if (!(len = ft_readfd(opt.infd, &input)))
		return (err_return("rsautl: unable to read input file\n"));
	if (len > 8)
	{
		free(input);
		return (err_return("rsautl: input too big\n"));
	}
	ft_memcpy(buf, input, len);
	free(input);
	if (*((uint64_t*)buf) > key.modulus)
		return (err_return("rsautl: input too big\n"));
	if (opt.decrypt)
	{
		if (opt.pubin)
			return err_return("rsautl: you're trying to decrypt with a pub key...\n");
		out = pow_mod(*((uint64_t*)buf), key.privateExponent, key.modulus);
	}
	else
		out = pow_mod(*((uint64_t*)buf), key.publicExponent, key.modulus);
	//fprintf(stderr, "in = %016lu\n", *((uint64_t*)buf));
	//fprintf(stderr, "in = %016lx\n", *((uint64_t*)buf));
	//fprintf(stderr, "key.modulus = %016lu\n", key.modulus);
	//fprintf(stderr, "key.privateExponent = %016lu\n", key.privateExponent);
	//fprintf(stderr, "key.publicExponent = %08u\n", key.publicExponent);
	//fprintf(stderr, "key.prime1 = %08u\n", key.prime1);
	//fprintf(stderr, "key.prime2 = %08u\n", key.prime2);
	//fprintf(stderr, "e * d = %016lu\n", ((uint64_t)key.privateExponent) * ((uint64_t)key.publicExponent));
	//fprintf(stderr, "(p - 1) * (q - 1) = %016lu\n", ((uint64_t)key.prime1 - 1) * ((uint64_t)key.prime2 - 1));
	if (opt.hexdump)
		write(2, "0000		", 6);
	i = 0;
	l = 7;
	while (((uint8_t*)&out)[l] == 0 && l >= 0)
		l--;
	while (i < l + 1)
	{
		if (opt.hexdump)
		{
			ft_putu8_hex_fd(((uint8_t*)&out)[i], 2);
			write(2, " ", 1);
		}
		ft_putchar_fd(((uint8_t*)&out)[i], opt.outfd);
		i++;
	}
	if (opt.hexdump)
		write(2, "\n", 1);
	//fprintf(stderr, "out = %016lu\n", out);
	//fprintf(stderr, "out = %016lx\n", out);
	return (1);
	//fprintf(stderr, "len = %d\n", len);
	//dprintf(opt.outfd, "%c%c%c%c%c%c%c%c",
	//		((uint8_t*)&out)[0],
	//		((uint8_t*)&out)[1],
	//		((uint8_t*)&out)[2],
	//		((uint8_t*)&out)[3],
	//		((uint8_t*)&out)[4],
	//		((uint8_t*)&out)[5],
	//		((uint8_t*)&out)[6],
	//		((uint8_t*)&out)[7]);
}
