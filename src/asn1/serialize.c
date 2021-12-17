/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:49:59 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/16 16:53:10 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <arpa/inet.h>

void				half_swap_array(uint8_t *buf, int len)
{
	int i;

	i = 0;
	while (i < len / 2)
	{
		((uint16_t*)buf)[i] = htons(((uint16_t*)buf)[i]);
		i++;
	}
}


int				encode_integer(uint8_t *i, int len, uint8_t *buf)
{
	buf[0] = 0x02;
	buf[1] = (uint8_t)len;
	ft_memcpy(&buf[2], i, len);
	return (2 + len);
}


void				rsa_deserializer(t_rsa_key key, uint8_t *buf, bool pub)
{
	buf[0] = 0x30; // SEQUENCE Identifier
	buf[1] = 59; // Lenght in octet of the whole sequence
	buf[2] = 0x02; // INTEGER Identifier
	buf[3] = 0x01; // Lenght in octet of the integer
	buf[4] = 0x00; // Version
	buf[5] = 0x02; // INTEGER Identifier
	buf[6] = 0x08; // Lenght in octet of the integer
	ft_memcpy(&buf[7], &key.modulus, 8); // modulus
	buf[15] = 0x02; // INTEGER Identifier
	buf[16] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[17], &key.publicExponent, 4); // publicExp
	if (pub)
		return ;
	buf[21] = 0x02; // INTEGER Identifier
	buf[22] = 0x08; // Lenght in octet of the integer
	ft_memcpy(&buf[23], &key.privateExponent, 8); // privateExp
	buf[31] = 0x02; // INTEGER Identifier
	buf[32] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[33], &key.prime1, 4); // prime1
	buf[41] = 0x02; // INTEGER Identifier
	buf[42] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[43], &key.prime2, 4); // prime2
	buf[51] = 0x02; // INTEGER Identifier
	buf[52] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[53], &key.exponent1, 4); // exponent1
	buf[61] = 0x02; // INTEGER Identifier
	buf[62] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[63], &key.exponent2, 4); // exponent2
	buf[71] = 0x02; // INTEGER Identifier
	buf[72] = 0x04; // Lenght in octet of the integer
	ft_memcpy(&buf[73], &key.coefficient, 4); // coefficient
//	half_swap_array(buf, 78);
	return ;
}

void				rsa_serializer(t_rsa_key *key, char *buf, bool pub)
{
	ft_memcpy(&key->modulus, &buf[7], 8); // modulus
	ft_memcpy(&key->publicExponent, &buf[17], 4); // publicExp
	if (pub)
		return ;
	ft_memcpy(&key->privateExponent, &buf[23], 8); // privateExp
	ft_memcpy(&key->prime1, &buf[33], 4); // prime1
	ft_memcpy(&key->prime2, &buf[43], 4); // prime2
	ft_memcpy(&key->exponent1, &buf[53], 4); // exponent1
	ft_memcpy(&key->exponent2, &buf[63], 4); // exponent2
	ft_memcpy(&key->coefficient, &buf[73], 4); // coefficient
	return ;
}

