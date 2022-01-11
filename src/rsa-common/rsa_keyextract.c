/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_keyextract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:00:12 by leon              #+#    #+#             */
/*   Updated: 2021/12/24 20:14:55 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "base64.h"
#include "des.h"

int			rsa_decrypt_key(char **input, int *len, char *paswd)
{
	void	*tmp;

	tmp = NULL;
	if (paswd)
	{
		if (!(get_des()))
			return (0);
		if (!(get_des()->opt->passwd = ft_strdup(paswd)))
			return (0);
	}
	if ((uint8_t)(*input)[0] == 1)
	{
		(*len)--;
		if (!(des_cbc(&tmp, (uint8_t*)(*input + 1), len, 1)))
			return (err_return("des-ecb enc failed\n"));
		free(*input);
		*input = tmp;
	}
	else if ((uint8_t)(*input)[0] == 2)
	{
		(*len)--;
		if (!(des_ecb(&tmp, (uint8_t*)(*input + 1), len, 1)))
			return (err_return("des-cbc enc failed\n"));
		free(*input);
		*input = tmp;
	}
	else if ((uint8_t)(*input)[0] == 0)
	{
		(*len)--;
		tmp = ft_memdup((*input) + 1, *len);
		free(*input);
		*input = tmp;
	}
	else
		return (err_return("enc_algo_id is not valid.\nBad key\n"));
	return (1);


}

int			rsa_extract_key(char **input, int *len, bool pub,
		char *paswd, t_list **top)
{
	void	*tmp;

	if (!parse_pem(input, pub, len))
		return (err_return("rsa_extract_key: parse-pem failed\n"));
        if (!(base64((void **)&tmp, (unsigned char*)(*input), len, 1)))
		return (err_return("rsa_extract_key: base64 decryption failed\n"));
	free(*input);
	*input = tmp;
	(void)paswd;
	//if (!(rsa_decrypt_key(input, len, paswd))) // TODO
	//	return (err_return("rsa_extract_key: des decryption failed\n"));
	asn_serialize(*input, *len, top);
	return (1);
}

int			rsa_extract_key_struct(char **input, int *len, bool pub,
		char *paswd, t_rsa_key *key)
{
	void	*tmp;

	if (!parse_pem(input, pub, len))
		return (err_return("rsa_extract_key: parse-pem failed\n"));
        if (!(base64((void **)&tmp, (unsigned char*)(*input), len, 1)))
		return (err_return("rsa_extract_key: base64 decryption failed\n"));
	free(*input);
	*input = tmp;
	(void)paswd;
	//if (!(rsa_decrypt_key(input, len, paswd))) // TODO
	//	return (err_return("rsa_extract_key: des decryption failed\n"));
	asn_serialize_struct(*input, *len, key);
	return (1);
}
