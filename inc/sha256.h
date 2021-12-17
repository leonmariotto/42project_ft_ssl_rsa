/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:07:23 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 18:48:18 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "libft.h"
# include "digest.h"

// TODO clean this
typedef struct      s_sha256
{
    t_opt               *opt;
}                   t_sha256;

unsigned char       *sha256(char *msg, int len);
char                *sha256_build_hash(u_int32_t *buf);
t_sha256            *get_sha256(void);
char                *sha256_build_hash(u_int32_t *buf);
u_int32_t           *sha256_by_msg_u32(char *msg, int len);
int                 sha256_by_fd(int fd);
int                 sha256_run_s_loop(void);
int                 sha256_run_files_loop(void);
int                 sha256_exit(void);

#endif
