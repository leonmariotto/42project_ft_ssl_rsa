/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 09:40:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:01:42 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "libft.h"
#include <stdio.h>

typedef struct          s_desopt
{
    char        a;
    char        d;
    char        v;
    char                pbkdf2;
    unsigned int        iter;
    int         input;
    int         output;
    char        *passwd;
}                       t_desopt;

typedef struct          s_keyring
{
    unsigned char    k[8];
    unsigned char    r[4];
    unsigned char    l[4];
}                       t_keyring;

typedef struct          s_des
{
    t_desopt        *opt;
    u_int8_t        *iv;
    u_int8_t        *key;
    t_keyring       *keyring;
    u_int8_t        *salt;
}                       t_des;

t_des               *get_des(void);

int                 des_get_opt(char **av, int ac);
void                print_opt(void);
int                 gen_salt(unsigned char **ptr);
int                 ask_paswd(char **ptr);
u_int8_t            *ossl_pbkdf(char *passwd, u_int8_t *salt,
                                size_t key_size, size_t iv_size);
int                 pbkdf2(char *passwd, size_t pass_len,
                                u_int8_t *salt, size_t salt_len,
                                size_t key_size, size_t iv_size,
                                unsigned int round);
t_keyring           *tkey(unsigned char *key);

int                 base64(void **ptr, const unsigned char *input, int *len, char mod);
int                 des_ecb(void **ptr, const unsigned char *input, int *len, char mod);
int                 des_cbc(void **ptr, const unsigned char *input, int *len, char mod);
int                 des3_ecb(void **ptr, const unsigned char *input, int *len, char mod);
int                 des3_cbc(void **ptr, const unsigned char *input, int *len, char mod);

// TODO opti
char                *des_blockey(char *buf, char mod, t_keyring *keys);

#endif
