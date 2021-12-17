/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_printout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:14:07 by leon              #+#    #+#             */
/*   Updated: 2021/12/16 17:03:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "base64.h"
#include "des.h"

int			print_pub(uint8_t *cyph, int len, uint8_t hdr, int fd)
{
	void	*b64;
	uint8_t	buf[2048];

	buf[0] = hdr;
	ft_memcpy(buf + 1, cyph, len);
	if (!base64(&b64, buf, &len, 0))
		return (0);
	ft_putendl_fd("----BEGIN PUBLIC KEY----", fd);
	print_base64(fd, b64, len);
	ft_putendl_fd("----END PUBLIC KEY----", fd);
	free(b64);
	return (1);
}

int			print_priv(uint8_t *cyph, int len, uint8_t hdr, int fd)
{
	void	*b64;
	uint8_t	buf[2048];

	buf[0] = hdr;
	ft_memcpy(buf + 1, cyph, len);
	if (!base64(&b64, buf, &len, 0))
		return (0);
	ft_putendl_fd("----BEGIN RSA PRIVATE KEY----", fd);
	print_base64(fd, b64, len);
	ft_putendl_fd("----END RSA PRIVATE KEY----", fd);
	free(b64);
	return (1);
}

int			rsa_print_out(t_rsa_key key, t_rsa_opt opt)
{
	void		*cyph;
	uint8_t		hdr;
	uint8_t		input[85];
	int		len;

	ft_bzero(input, 84);
	rsa_deserializer(key, input, opt.pubin);
	hdr = 0;
	len = (opt.pubout || opt.pubin ? 24 : 84);
	if (opt.passout)
	{
		if (!(get_des()))
			return (0);
		if (!(get_des()->opt->passwd = ft_strdup(opt.passout)))
			return (0);
	}
	if (opt.des_ecb)
	{
		if (!(des_ecb(&cyph, input, &len, 0)))
			return (err_return("des-ecb enc failed\n"));
		hdr = 2;
	}
	else if (opt.des_cbc)
	{
		if (!(des_cbc(&cyph, input, &len, 0)))
			return (err_return("des-cbc enc failed\n"));
		hdr = 1;
	}
	else
	{
		if (!(cyph = ft_memdup((char*)input, len)))
			return (err_return("malloc error"));
	}
	if (opt.pubin || opt.pubout)
	{
		if (!(print_pub(cyph, len, hdr, opt.outfd)))
			return (0);
		free(cyph);
		return (1);
	}
	if (!(print_priv(cyph, len, hdr, opt.outfd)))
		return (0);
	free(cyph);
	return (1);
}
