/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:46:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/17 17:21:14 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int				encode_integer(uint8_t *i, uint8_t *buf, int len)
{
	buf[0] = 0x02;
	buf[1] = (uint8_t)len;
	ft_memcpy(&buf[2], i, len);
	return (2 + len);
}

void				rsa_deserializer(t_rsa_key key, uint8_t *buf, bool pub)
{
	int i;
	uint8_t version;

	i = 0;
	version = 0x00;
	buf[i++] = 0x30;
	buf[i++] = pub ? 18 : 60;
	i += encode_integer((uint8_t*)&version, &buf[i], 1);
	i += encode_integer((uint8_t*)&key.modulus, &buf[i], 8);
	i += encode_integer((uint8_t*)&key.publicExponent, &buf[i], 3);
	if (pub)
		return ;
	i += encode_integer((uint8_t*)&key.privateExponent, &buf[i], 8);
	i += encode_integer((uint8_t*)&key.prime1, &buf[i], 5);
	i += encode_integer((uint8_t*)&key.prime2, &buf[i], 5);
	i += encode_integer((uint8_t*)&key.exponent1, &buf[i], 4);
	i += encode_integer((uint8_t*)&key.exponent2, &buf[i], 4);
	i += encode_integer((uint8_t*)&key.coefficient, &buf[i], 4);
}

int				ft_memcpy_inv(void *dst, void *src, int size)
{
	int i;
	int j;

	i = size - 1;
	j = 0;
	while (i >= 0)
	{
		((uint8_t*)dst)[j] = ((uint8_t*)src)[i];
		i--;
		j++;
	}
	return (1);
}

int				decode_integer(uint8_t *buf, t_asn_obj *obj)
{
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		hlen;
	int		i;

	i = 1;
	len_len = 1;
	if (buf[i] & 0x80)
		len_len = (buf[i++] ^ 0x80);
	ft_bzero(&len, 8);
	ft_memcpy_inv(&len, &buf[i], len_len);
	hlen = i + len_len;
	obj->id = buf[0];
	obj->len = len;
	if (!(obj->content = malloc(len)))
		return (err_return("asn: error"));
	ft_memcpy(obj->content, &buf[hlen], len);
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
		len_len = (buf[i++] ^ 0x80);
	ft_bzero(&len, 8);
	ft_memcpy_inv(&len, &buf[i], len_len);
	i += len_len;
	hlen = i;
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

int				rsa_serializer(char *buf, int len, t_list **top) // is pub needed ??
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
