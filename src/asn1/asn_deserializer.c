/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn_deserializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:46:29 by lmariott          #+#    #+#             */
/*   Updated: 2022/02/07 14:03:53 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"


// MEEEEEEEEEEERDE faut que j'ai une trace de la SEQUENCE...
// J'en ai besoin pour faire la len ??
// None pas besoin, fonction séparé de la main loop qui mesure les int et en 
// deduit la taille de la sequence (pub ou priv)
// Donc bene
uint64_t			get_seq_len(t_list *top, bool pub)
{
	t_list		*head;
	uint64_t	len;
	int		pub_counter;
	t_asn_obj *obj;

	head = top;
	pub_counter = 0;
	len = 0;
	while (head)
	{
		obj = head->content;
		//fprintf(stderr, "len_len = %d ; len = %ld\n", ((t_asn_obj*)head->content)->len_len, ((t_asn_obj*)head->content)->len);
		//uint8_t j = 0;
		//while (j < ((t_asn_obj*)head->content)->len)
		//	fprintf(stderr, "%hhx:", obj->content[j++]);
		//fprintf(stderr, "\n");
		len += 1 + obj->len_len + obj->len;
		pub_counter++;
		if (pub && pub_counter >= 3)
			break;
		head = head->next;
	}
	return (len);
}

int				asn_deserialize(t_list *top, bool pub,
					uint8_t **ptr)
{
	t_list		*head;
	uint8_t		*msg;
	uint64_t	len;
	uint8_t		len_len;
	int		i;
	int		pub_counter;

	len = get_seq_len(top, pub);
	len_len = (len >= 128 ? 2 : 1);
	if (!(msg = malloc(len + len_len + 1)))
		return (0);
fprintf(stderr, "len = %ld ; len_len = %d\n", len, len_len);
	i = 0;
	pub_counter = 0;
	msg[i++] = 0x30;
	if (len_len == 2)
		msg[i++] = 0x82;
	ft_memcpy_inv(&msg[i], &len, len_len);
	i += len_len;
	head = top;
	while (head)
	{
		msg[i++] = 0x02;
		ft_memcpy_inv(&msg[i], &((t_asn_obj*)head->content)->len,
			((t_asn_obj*)head->content)->len_len);
		i += ((t_asn_obj*)head->content)->len_len;
//		if (((t_asn_obj*)head->content)->content[0] == 0 &&
//			((t_asn_obj*)head->content)->len != 1)
		if (((t_asn_obj*)head->content)->content[((t_asn_obj*)head->content)->len] & 0x80)
		{
			// TODO MODIFY THE LEN AT SERIALIZE AND DESERIALIZE???
			msg[i] = 0x00;
			//msg[i + ((t_asn_obj*)head->content)->len] = 0x00;
	//		ft_memcpy(&msg[i], &((t_asn_obj*)head->content)->content[1],
	//			((t_asn_obj*)head->content)->len - 1);
			//ft_memcpy_inv(&msg[i + 1], ((t_asn_obj*)head->content)->content,
			//	((t_asn_obj*)head->content)->len - 1);
			//ft_memcpy(&msg[i + 1], ((t_asn_obj*)head->content)->content,
			//	((t_asn_obj*)head->content)->len - 1);
			ft_memcpy_inv(&msg[i + 1], ((t_asn_obj*)head->content)->content,
				((t_asn_obj*)head->content)->len - 1);
		}
		else
		{
			//ft_memcpy_inv(&msg[i], ((t_asn_obj*)head->content)->content,
			//	((t_asn_obj*)head->content)->len);
			ft_memcpy_inv(&msg[i], ((t_asn_obj*)head->content)->content,
				((t_asn_obj*)head->content)->len);
		}
		i += ((t_asn_obj*)head->content)->len;
		head = head->next;
		pub_counter++;
		if (pub && pub_counter >= 3)
			break;
	}
	*ptr = msg;
	return (i);
}
