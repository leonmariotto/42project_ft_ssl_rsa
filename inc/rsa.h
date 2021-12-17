/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:22:53 by leon              #+#    #+#             */
/*   Updated: 2021/12/17 12:01:55 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include "libft.h"
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>

/*
** modulus is the RSA modulus n.
** publicExponent is the RSA public exponent e.
** privateExponent is the RSA private exponent d.
** prime1 is the prime factor p of n.
** prime2 is the prime factor q of n.
** exponent1 is d mod (p - 1).
** exponent2 is d mod (q - 1).
** coefficient is the CRT coefficient q^(-1) mod p.
** estce que les sizes sont bonnes ?? quand on print text avec openssl
** modulus est 2 * plus grand que prime* ...
*/

typedef struct			s_rsa_key
{
	uint64_t	modulus;
	uint32_t	publicExponent;
	uint64_t	privateExponent;
	uint32_t	prime1;
	uint32_t	prime2;
	uint32_t	exponent1;
	uint32_t	exponent2;
	uint32_t	coefficient;
} 				t_rsa_key;

//} __attribute__((packed))	t_rsa_private_key;
//typedef enum  e_enc_type {
//	NONE,
//	DES_CBC,
//	DES_ECB,
//	DES3_CBC,
//	DES3_ECB
//} enc_type;

// 0 == NONE
// 1 == DES_CBC
// 2 == DES_ECB
// 3 == DES3_CBC
// 4 == DES3_ECB

typedef struct			s_key_hdr
{
	uint8_t		enc_algo_id;
} __attribute__((packed)) 	t_key_hdr;

typedef struct			s_genrsa_opt
{
	int	randomfd;
	int	outfd;
} 				t_genrsa_opt;

// TODO : -----BEGIN ENCRYPTED PUBLIC KEY-----
// TODO : B64 DATA
// TODO : -----END ENCRYPTED PUBLIC KEY-----
// TODO : Add the attribute packed to every struct as i will print struct directly
// TODO : s_enc_hdr is at the begining of every B64 DATA because :
// 		1 - I don't have to respect pkcs1 ou pkcs8
// 		2 - It's stupid to store a secret unencrypted


typedef struct			s_rsa_opt
{
	int		infd;
	int		outfd;
	char		*passin;
	char		*passout;
	bool		des_cbc;
	bool		des_ecb;
	bool		text;
	bool		noout;
	bool		modulus;
	bool		check;
	bool		pubin;
	bool		pubout;
}				t_rsa_opt;

typedef struct			s_rsautl_opt
{
	int		infd;
	char		*pass;
	int		outfd;
	int		keyfd;
	bool		pubin;
	bool		decrypt;
	bool		hexdump;
}				t_rsautl_opt;

typedef struct			s_asn_obj
{
	uint8_t		id;
	uint8_t		len_len;
	uint64_t	len;
	uint8_t		*content;
}				t_asn_obj;

int			open_randomfd(char *file);
uint64_t		gen_prime(int randomfd, bool verb);
int			get_random(void	*ptr, size_t size, int randomfd);
int			gen_enckey(uint32_t p, uint32_t q, int randomfd);
uint32_t		euclide(uint32_t a, uint32_t b);
uint64_t		lcm(uint64_t a, uint64_t b);
//uint64_t			gcd_extended(uint64_t a, uint64_t b,
//		uint64_t *u, uint64_t *v);
//uint64_t			gcd_extended(int64_t a, int64_t b,
//		int64_t *u, int64_t *v);
int64_t		gcd_extended(int64_t a, int64_t b, int64_t *u, int64_t *v);
uint64_t		pow_mod(uint64_t a, uint64_t b, uint64_t mod);

void			print_modulus(t_list *top);
int			rsa_print_out(t_rsa_key key, t_rsa_opt opt);
//int			print_text(t_rsa_key key, bool pub);
int			first_parse(char **input, bool pub, int *len);
int			rsa_getopt(t_rsa_opt *opt, void **av, int ac);
int			rsa_extract_key(char **input, int *len, bool pub,
		char *paswd, t_list **top);
int			parse_pem(char **input, bool pub, int *len);
void				rsa_deserializer(t_rsa_key key, uint8_t *buf, bool pub);
int				rsa_serializer(char *buf, int len, t_list **top);
uint64_t		mult_mod(uint64_t a, uint64_t b, uint64_t mod);
void			print_text(t_list *top, t_rsa_opt opt);
int			check_key(t_list *top);

#endif

