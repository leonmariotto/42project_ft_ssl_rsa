/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn_serializer_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:30:23 by leon              #+#    #+#             */
/*   Updated: 2022/01/13 18:46:34 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void				key_store_value(t_rsa_key *key, uint8_t *buf,
			int len, int counter)
{
	if (counter == 1)
		ft_memcpy_inv(&key->modulus, buf, len);
	else if (counter == 2)
		ft_memcpy_inv(&key->publicExponent, buf, len);
	else if (counter == 3)
		ft_memcpy_inv(&key->privateExponent, buf, len);
	else if (counter == 4)
		ft_memcpy_inv(&key->prime1, buf, len);
	else if (counter == 5)
		ft_memcpy_inv(&key->prime2, buf, len);
	else if (counter == 6)
		ft_memcpy_inv(&key->exponent1, buf, len);
	else if (counter == 7)
		ft_memcpy_inv(&key->exponent2, buf, len);
	else if (counter == 8)
		ft_memcpy_inv(&key->coefficient, buf, len);

		
}

int				decode_integer_struct(uint8_t *buf, t_rsa_key *key, int counter)
{
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		hlen;
	int		i;
	int		ad;

	if (!counter)
		return (3);
	i = 1;
	len_len = 1;
	if (buf[i] & 0x80)
		return (err_return("asn: integer lenght too long, only handle len<=128"));
	ft_bzero(&len, 8);
	ft_memcpy_inv(&len, &buf[i], len_len);
	hlen = i + len_len;
	ad = (buf[hlen] == 0 ? 1 : 0);
	if (len - ad > 8)
		return (err_return("asn: invalid lenght\n"));
	key_store_value(key, &buf[hlen + ad], (int)len - ad, counter);
	return (len + hlen);
}

int				decode_sequence_struct(uint8_t *buf, t_rsa_key *key)
{
	uint64_t		i;
	int			r;
	int			c;
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		hlen;
	t_asn_obj		*new;

	i = 1;
	len_len = 1;
	if (buf[i] & 0x80)
		return (err_return("asn: sequence lenght too long, only handle len<=128"));
	ft_bzero(&len, 8);
	ft_memcpy_inv(&len, &buf[i], len_len);
	i += len_len;
	hlen = i;
	c = 0;
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
			if(!(r = decode_integer_struct(&buf[i], key, c++)))
				return (0);
			i += (uint64_t)r;
		}
		else
		{
			return (err_return("asn1: unknow identifier, please dont retry\n"));
		}
	}
	return (len + hlen);
}

int				asn_serialize_struct(char *buf, int len, t_rsa_key *key)
{
	int		i;
	int		r;

	i = 0;
	while (i < len)
	{
		if (buf[i] == 0x30)
		{
			if (!(r = decode_sequence_struct((uint8_t*)&buf[i], key)))
				return (0);
			i += r;
		}
		else
			return (err_return("asn1: unknow identifier, please dont retry\n"));
	}
	return (1);
}
