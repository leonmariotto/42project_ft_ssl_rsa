/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rsautl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:18:36 by leon              #+#    #+#             */
/*   Updated: 2022/01/12 19:18:12 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

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
	int		l;

	ft_bzero(&opt, sizeof(opt));
	if (!(rsautl_getopt(&opt, av, ac)))
		return (0);
	if (!opt.keyfd)
		return (err_return("rsautl: You have to specify a key\n"));
	if (!(len = ft_readfd(opt.keyfd, &input)))
		return (err_return("rsautl: unable to read key file\n"));
	if (!(rsa_extract_key_struct(&input, &len, opt.pubin, opt.pass, &key)))
		return (0);
	free(input);
	ft_bzero(buf, 8);
	if (!(len = ft_readfd(opt.infd, &input)))
		return (err_return("rsautl: unable to read input file\n"));
	if (len > 8)
	{
		free(input);
		return (err_return("rsautl: input too big\n"));
	}
	ft_memcpy_inv(buf, input, len);
	free(input);
	if (*((uint64_t*)buf) > key.modulus)
		return (err_return("rsautl: input too big\n"));
	//fprintf(stderr, "buf = %016lu\n", (*(uint64_t*)buf));
	//fprintf(stderr, "key.modulus = %016lx\n", key.modulus);
	//fprintf(stderr, "key.privateExponent = %016lx\n", key.privateExponent);
	//fprintf(stderr, "key.publicExponent = %08x\n", key.publicExponent);
	//fprintf(stderr, "key.prime1 = %08x\n", key.prime1);
	//fprintf(stderr, "key.prime2 = %08x\n", key.prime2);
	//fprintf(stderr, "e * d = %016lu\n", ((uint64_t)key.privateExponent) * ((uint64_t)key.publicExponent));
	//fprintf(stderr, "(p - 1) * (q - 1) = %016lu\n", ((uint64_t)key.prime1 - 1) * ((uint64_t)key.prime2 - 1));
	//out = *(uint64_t*)buf;
	//i = 0;
	//while (i < len)
	//{
	//	out <<= 8;
	//	out |= (uint64_t)buf[i++];
	//	fprintf(stderr, "msg[%d] = %016lu\n", i, out);
	//}
	if (opt.decrypt)
	{
		if (opt.pubin)
			return err_return("rsautl: you're trying to decrypt with a pub key...\n");
		out = pow_mod((*(uint64_t*)buf), key.privateExponent, key.modulus);
	}
	else
		out = pow_mod((*(uint64_t*)buf), key.publicExponent, key.modulus);
	//fprintf(stderr, "out = %016lu\n", out);
	if (opt.hexdump)
		write(2, "0000		", 6);
	l = 7;
	while (((uint8_t*)&out)[l] == 0 && l >= 0)
		l--;
	while (l + 1)
	{
		if (opt.hexdump)
		{
			ft_putu8_hex_fd(((uint8_t*)&out)[l], 2);
			write(2, " ", 1);
		}
		ft_putchar_fd(((uint8_t*)&out)[l], opt.outfd);
		l--;
	}
	//while (i < l + 1)
	//{
	//	if (opt.hexdump)
	//	{
	//		ft_putu8_hex_fd(((uint8_t*)&out)[i], 2);
	//		write(2, " ", 1);
	//	}
	//	ft_putchar_fd(((uint8_t*)&out)[i], opt.outfd);
	//	i++;
	//}
	if (opt.hexdump)
		write(2, "\n", 1);
	return (1);
}
