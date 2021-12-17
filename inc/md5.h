/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:05:25 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 18:48:09 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include "digest.h"

// TODO clean this
typedef struct		s_md5 
{
    t_opt               *opt;
}		            t_md5;

t_md5	*get_md5(void); 


int                 md5_by_fd(int fd);
u_int32_t           leftrotate(u_int32_t x, char c);
void                process_md5(char *buf, unsigned int *vars);
char                *md5_build_hash(u_int32_t *buf);
int                 md5_run_s_loop(void);
int                 md5_run_files_loop(void);
unsigned char       *md5(char *msg, int len);
int                 md5_exit(void);


#endif
