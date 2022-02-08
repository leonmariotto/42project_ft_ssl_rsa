/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_keyextract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:00:12 by leon              #+#    #+#             */
/*   Updated: 2022/02/08 20:35:27 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "base64.h"
#include "des.h"

int			check_des_encryption(uint8_t **input, int *len, uint8_t **salt)
{
	void		*tmp;
	//t_des		*des;

	if (!ft_memcmp((char*)*input, "Proc-Type:", 10))
	{
		// OK There is an encryption, do we handle it ?
		if (ft_memcmp((char*)(*input + 10), "4,ENCRYPTEDDEK-Info:", 20))
			return (err_return("Dont try this plz\n"));
		if (!ft_memcmp((char*)(*input + 30), "DES-CBC", 7))
		{
			// CBC 
			//des = get_des();
			*salt = ft_ahextovbin((char*)(*input + 38), 16);
			//uint8_t		salted[8];
			//int i = -1;
			//while (++i < 8)
			//	salted[i] = (*salt)[7 - i];
			//ft_memcpy(*salt, salted, 8);
			fprintf(stderr, "salt = [%x %x %x %x %x %x %x %x]\n",
				(*salt)[0],
				(*salt)[1],
				(*salt)[2],
				(*salt)[3],
				(*salt)[4],
				(*salt)[5],
				(*salt)[6],
				(*salt)[7]);
			//des->opt->passwd = passwd;
			*len -= 54;
			tmp = ft_memdup((char*)(*input + 54), *len);
			free(*input);
			*input = tmp;
			//des_cbc(&tmp, *input + 58, len, 1);
			//*input = tmp;
			return (2);
		}
		else if (!ft_memcmp((char*)(*input + 43 + 22), "DES-ECB", 7))
		{
			// ECB 
			//des = get_des();
			//des->opt->passwd = passwd;
			*salt = ft_ahextovbin((char*)(*input + 37), 8);
			int i = -1;
			while (++i < 8)
				(*salt)[i] = (*salt)[7 - i];
			*len -= 54;
			tmp = ft_memdup((char*)(*input + 54), *len);
			free(*input);
			*input = tmp;
			//des_ecb(&tmp, *input + 58, len, 1);
			//*input = tmp;
			return (1);
		}
		else
			err_return("rsa key: unknow Header");
	}
	return (3);
}


int			rsa_decrypt_key(char **input, int *len, char *paswd, int des, uint8_t *salt)
{
	void	*tmp;

	tmp = NULL;
	if (!(get_des()))
		return (0);
	get_des()->salt = salt;
	get_des()->iv = ft_memdup((char*)salt, 8);
	if (paswd)
	{
		if (!(get_des()))
			return (0);
		if (!(get_des()->opt->passwd = ft_strdup(paswd)))
			return (0);
	}
	if (des == 2)
	{
		if (!(des_cbc(&tmp, (uint8_t*)(*input), len, 1)))
			return (err_return("des-ecb enc failed\n"));
		free(*input);
		*input = tmp;
	}
	else if (des == 1)
	{
		if (!(des_ecb(&tmp, (uint8_t*)(*input), len, 1)))
			return (err_return("des-cbc enc failed\n"));
		free(*input);
		*input = tmp;
	}
	else
	{
		return (1);
	}
	return (1);


}

int			rsa_extract_key(char **input, int *len, bool pub,
		char *paswd, t_list **top)
{
	void	*tmp;
	int	des;
	uint8_t	*salt;

	if (!parse_pem(input, pub, len))
		return (err_return("rsa_extract_key: parse-pem failed\n"));
	if (!(des = check_des_encryption((uint8_t**)input, len, &salt))) // TODO
		return (err_return("rsa_extract_key: des decryption failed\n"));
        if (!(base64((void **)&tmp, (unsigned char*)(*input), len, 1)))
		return (err_return("rsa_extract_key: base64 dec failed\n"));
	free(*input);
	*input = tmp;
	(void)paswd;
	if (!(rsa_decrypt_key(input, len, paswd, des, salt)))
		return (err_return("rsa_extract_key: des decryption failed"));
	if (!(asn_serialize(*input, *len, top)))
		return (0);
	return (1);
}

int			rsa_extract_key_struct(char **input, int *len, bool pub,
		char *paswd, t_rsa_key *key)
{
	void	*tmp;
	int	des;
	uint8_t	*salt;

	if (!parse_pem(input, pub, len))
		return (err_return("rsa_extract_key: parse-pem failed\n"));
	if (!(des = check_des_encryption((uint8_t**)input, len, &salt))) // TODO
		return (err_return("rsa_extract_key: des decryption failed\n"));
        if (!(base64((void **)&tmp, (unsigned char*)(*input), len, 1)))
		return (err_return("rsa_extract_key: base64 decryption failed\n"));
	free(*input);
	*input = tmp;
	if (!(rsa_decrypt_key(input, len, paswd, des, salt)))
		return (err_return("rsa_extract_key: des decryption failed"));
	if (!(asn_serialize_struct(*input, *len, key)))
		return (0);
	return (1);
}
