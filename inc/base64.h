/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 10:57:59 by lmariott          #+#    #+#             */
/*   Updated: 2021/10/19 14:22:54 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "libft.h"

typedef struct		s_base64opt {
    int     d;
    int     input;
    int     output;
}		            t_base64opt;

typedef struct		s_base64 {
    t_base64opt         *opt;
}		            t_base64;

t_base64	*get_base64(void); 
int         base64(void **ptr, const unsigned char *input, int *len, char mod);
int         encode_base64(void);
int         decode_base64(void);
void        exit_base64(void);
void        print_base64(int fd, char  *output, int len);




#endif

