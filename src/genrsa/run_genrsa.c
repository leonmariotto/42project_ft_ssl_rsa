/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_genrsa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:26:45 by lmariott          #+#    #+#             */
/*   Updated: 2022/01/10 13:04:05 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "base64.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int				encode_integer(uint8_t *j, uint8_t *buf, int len, uint8_t add)
{
	int	i;
	uint8_t	inv[len];
	uint8_t nadd;

(void)add; // todo remove
	i = 0;
	ft_memcpy_inv(inv, j, len);
	nadd = (inv[0] & 0x80 ? 1 : 0);
	buf[i++] = 0x02;
	buf[i++] = (uint8_t)len + nadd;
	if (nadd)
		buf[i++] = 0x00;
	//ft_memcpy_inv(&buf[i], j, len);
	ft_memcpy(&buf[i], inv, len);
	//if (add)
	//	buf[len] = 0x00;
	return (2 + len + nadd);
}

uint32_t			rsa_deserializer_genrsa(t_rsa_key key, uint8_t *buf, bool pub)
{
	uint32_t	i;
	uint8_t		version;

	i = 0;
	version = 0x00;
	buf[i++] = 0x30;
	i++;
	//buf[i++] = pub ? 18 : 61;
	i += encode_integer((uint8_t*)&version, &buf[i], 1, 0);
	i += encode_integer((uint8_t*)&key.modulus, &buf[i], 8, 
			((uint8_t*)&key.modulus)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.publicExponent, &buf[i], 3, 0);
	if (pub)
		return (i);
	i += encode_integer((uint8_t*)&key.privateExponent, &buf[i], 8,
			((uint8_t*)&key.privateExponent)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.prime1, &buf[i], 4,
			((uint8_t*)&key.prime1)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.prime2, &buf[i], 4,
			((uint8_t*)&key.prime2)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.exponent1, &buf[i], 4,
			((uint8_t*)&key.exponent1)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.exponent2, &buf[i], 4,
			((uint8_t*)&key.exponent2)[0] & 0x80 ? 1 : 0);
	i += encode_integer((uint8_t*)&key.coefficient, &buf[i], 4,
			((uint8_t*)&key.coefficient)[0] & 0x80 ? 1 : 0);
	buf[1] = (uint8_t)(i - 2);
	return (i);
}
int				gen_pkey(t_rsa_key *pkey, int randomfd)
{
	int64_t		tmp;
	int64_t		u;
	int64_t		v;

	u = 0;
	v = 0;
	if (randomfd < 0 && !(randomfd = open_randomfd(NULL)))
		return (0);
	if (!(pkey->prime1 = gen_prime(randomfd, true))
		|| !(pkey->prime2 = gen_prime(randomfd, true)))
		return (0);
	(*pkey).modulus = (uint64_t)(*pkey).prime1 * (uint64_t)(*pkey).prime2;
	(*pkey).publicExponent = 65537;
	tmp = lcm((*pkey).prime1 - 1, (*pkey).prime2 - 1);
	(*pkey).privateExponent = 0;
	if (gcd_extended((*pkey).publicExponent, tmp, &u, &v) != 1)
	       err_return("Error: there is no modulare multiplicative inverse here, retry");
	(*pkey).privateExponent = (u % (int64_t)tmp + (int64_t)tmp) % (int64_t)tmp;
	(*pkey).exponent1 = (*pkey).privateExponent % ((*pkey).prime1 - 1);
	(*pkey).exponent2 = (*pkey).privateExponent % ((*pkey).prime2 - 1);
	(*pkey).coefficient = pow_mod((*pkey).prime2, (*pkey).prime1 - 2, (*pkey).prime1);
	close(randomfd);
	return (1);
}

int				genrsa_getopt(t_genrsa_opt *opt, void **av, int ac)
{
	int	i;

	i = 1;
	(*opt).randomfd = -1;
	(*opt).outfd = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-i"))
		{
			++i;
			if (!((*opt).randomfd = open(av[i], O_RDONLY)))
				return (err_return("genrsa_getopt: open error\n"));
		}
		else if (!ft_strcmp(av[i], "-o"))
		{
			++i;
			if (!((*opt).outfd = open(av[i], O_CREAT |
					O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)))
				return (err_return("genrsa_getopt: open error\n"));

		}
	}
	return (1);
}

int				run_genrsa(void **av, int ac)
{
	t_rsa_key		pkey;
	t_genrsa_opt		opt;
	void			*b64ptr;
	uint32_t			len;
	char			buf[84];

	if (!(genrsa_getopt(&opt, av, ac)))
		return (0);
	ft_putendl_fd("Generating RSA private key, 64 bit long modulus", 2);
	if (!gen_pkey(&pkey, opt.randomfd))
		return (0);
	fprintf(stderr, "key.modulus = %016lx\n", pkey.modulus);
	fprintf(stderr, "key.privateExponent = %016lx\n", pkey.privateExponent);
	fprintf(stderr, "key.publicExponent = %08x\n", pkey.publicExponent);
	fprintf(stderr, "key.prime1 = %08x\n", pkey.prime1);
	fprintf(stderr, "key.prime2 = %08x\n", pkey.prime2);
	ft_putendl_fd("e is 65537 (0x10001)", 2);
	ft_bzero(buf, 84);
	len = rsa_deserializer_genrsa(pkey, (uint8_t*)buf, 0);
	b64ptr = NULL;
	base64((void **)&b64ptr, (unsigned char *)buf, (int*)&len, 0);
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", opt.outfd);
	print_base64(opt.outfd, b64ptr, len);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", opt.outfd);
	free(b64ptr);

	return (1);
}
