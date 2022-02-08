/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_printout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:14:07 by leon              #+#    #+#             */
/*   Updated: 2022/02/08 20:44:33 by leon             ###   ########.fr       */
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
	ft_putendl_fd("-----BEGIN PUBLIC KEY-----", fd);
	print_base64(fd, b64, len);
	ft_putendl_fd("-----END PUBLIC KEY-----", fd);
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
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", fd);
	print_base64(fd, b64, len);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", fd);
	free(b64);
	return (1);
}

int			rsa_print_out(t_list *top, t_rsa_opt opt)
{
	uint8_t		*msg;
	void		*b64;
	void		*des;
	uint8_t		*salt;
	int		len;

	if (opt.pubout || opt.pubin)
		ft_putendl_fd("-----BEGIN PUBLIC KEY-----", opt.outfd);
	else
		ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", opt.outfd);
	if (!(len = asn_deserialize(top, opt.pubout || opt.pubin, &msg)))
		return (0);
	if (opt.des_cbc || opt.des_ecb)
	{
		ft_putendl_fd("Proc-Type: 4,ENCRYPTED", opt.outfd);
		if (!(gen_salt(&salt)))
			return (err_return("gen_salt"));
		if (opt.des_cbc)
		{
			ft_putstr_fd("DEK-Info: DES-CBC,", opt.outfd);
			int i = 0;
			while (i < 8)
				ft_putu8_hex_fd(salt[i++], opt.outfd);
			ft_putstr_fd("\n\n", opt.outfd);
			if (!get_des())
				return (0);
			get_des()->salt = salt;
			get_des()->iv = salt;
			get_des()->opt->passwd = NULL;
			get_des()->opt->nosalt = 1;
			get_des()->opt->pbkdf2 = 0;
			des_cbc(&des, (uint8_t*)msg, &len, 0);
			//free(msg);
			msg = des;
		}
		else
		{
			ft_putstr_fd("DEK-Info: DES-ECB,", opt.outfd);
			int i = 0;
			while (i < 8)
				ft_putu8_hex_fd(salt[i++], opt.outfd);
			ft_putstr_fd("\n\n", opt.outfd);
			if (!get_des())
				return (0);
			get_des()->salt = salt;
			get_des()->iv = salt;
			get_des()->opt->passwd = NULL;
			get_des()->opt->nosalt = 1;
			get_des()->opt->pbkdf2 = 0;
			des_ecb(&des, msg, &len, 0);
			//free(msg);
			msg = des;
		}
	}
	if (!base64(&b64, msg, &len, 0))
		return (0);
	// TODO : IF ENCRYPTION ASKED, encrypt, print header, return output
	print_base64(opt.outfd, b64, len);
	if (opt.pubout || opt.pubin)
		ft_putendl_fd("-----END PUBLIC KEY-----", opt.outfd);
	else
		ft_putendl_fd("-----END RSA PRIVATE KEY-----", opt.outfd);
	return (0);
}

//int			rsa_print_out(t_rsa_key key, t_rsa_opt opt)
//{
//	void		*cyph;
//	uint8_t		hdr;
//	uint8_t		input[85];
//	int		len;
//
//	ft_bzero(input, 84);
//	rsa_deserializer(key, input, opt.pubin);
//	hdr = 0;
//	len = (opt.pubout || opt.pubin ? 24 : 84);
//	if (opt.passout)
//	{
//		if (!(get_des()))
//			return (0);
//		if (!(get_des()->opt->passwd = ft_strdup(opt.passout)))
//			return (0);
//	}
//	if (opt.des_ecb)
//	{
//		if (!(des_ecb(&cyph, input, &len, 0)))
//			return (err_return("des-ecb enc failed\n"));
//		hdr = 2;
//	}
//	else if (opt.des_cbc)
//	{
//		if (!(des_cbc(&cyph, input, &len, 0)))
//			return (err_return("des-cbc enc failed\n"));
//		hdr = 1;
//	}
//	else
//	{
//		if (!(cyph = ft_memdup((char*)input, len)))
//			return (err_return("malloc error"));
//	}
//	if (opt.pubin || opt.pubout)
//	{
//		if (!(print_pub(cyph, len, hdr, opt.outfd)))
//			return (0);
//		free(cyph);
//		return (1);
//	}
//	if (!(print_priv(cyph, len, hdr, opt.outfd)))
//		return (0);
//	free(cyph);
//	return (1);
//}
