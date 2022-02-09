/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn_serializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:30:23 by leon              #+#    #+#             */
/*   Updated: 2022/02/09 19:39:40 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int				decode_integer(uint8_t *buf, t_asn_obj *obj)
{
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		hlen;
	int		i;
	int		ad;

	i = 1;
	len_len = 1;
	if (buf[i] & 0x80)
		return (err_return("asn: sequence lenght too long, only handle len<=128"));
		//len_len = (buf[i++] ^ 0x80);
	ft_bzero(&len, 8);
	ft_memcpy(&len, &buf[i], len_len);
	hlen = i + len_len;
	obj->id = buf[0];
	obj->len = len;
	obj->len_len = len_len;
	ad = (buf[hlen] == 0 ? 1 : 0);
	if (len - ad != 0)
	{
		if (!(obj->content = ft_memalloc(len - ad)))
			return (err_return("asn: error"));
		ft_memcpy_inv(obj->content, &buf[hlen + ad], len - ad);
	}
	else
	{
		if (!(obj->content = ft_memalloc(1)))
			return (err_return("asn: error"));
	}
	//fprintf(stderr, "hlen : %x ; ad : %x\n", hlen, ad);
	//fprintf(stderr, "first byte of obj content : %x\n", buf[hlen + ad]);
	//fprintf(stderr, "buf[hlen] : %x\n", buf[hlen]);
	return (len + hlen);
}

int				decode_sequence(uint8_t *buf, t_list **top)
{
	uint64_t		i;
	int			r;
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		hlen;
	t_asn_obj		*new;

	i = 1;
	len_len = 1;
	if (buf[i] & 0x80)
		return (err_return("asn: sequence lenght too long, only handle len<=128"));
		//len_len = (buf[i++] ^ 0x80);
	ft_bzero(&len, 8);
	ft_memcpy(&len, &buf[i], len_len);
	i += len_len;
	hlen = i;
	//fprintf(stderr, "decode: len of the sequence = %lu\n", len);
	//fprintf(stderr, "buf = ");
	//uint8_t j = 0;
	//while (j < len)
	//	fprintf(stderr, "%hhx:", buf[j++]);
	//fprintf(stderr, "\n");
	while (i < len + hlen)
	{
		if (buf[i] == 0x02)
		{
			if (!(new = ft_memalloc(sizeof(t_asn_obj))))
				return (err_return("asn: malloc"));
			if(!(r = decode_integer(&buf[i], new)))
				return (0);
			i += (uint64_t)r;
			ft_lstpush(top, ft_lstnew_nodup(new, sizeof(t_asn_obj)));
		}
		else
		{
			return (err_return("asn1: unknow identifier, please dont retry\n"));
		}
	}
	return (len + hlen);
}

int				asn_serialize(char *buf, int len, t_list **top)
{
	int		i;
	int		r;

	i = 0;
	while (i < len)
	{
		if (buf[i] == 0x30)
		{
			if (!(r = decode_sequence((uint8_t*)&buf[i], top)))
				return (0);
			i += r;
		}
		else
			return (err_return("asn1: unknow identifier, please dont retry\n"));
	}
	return (1);
}
