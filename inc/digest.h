/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:36:51 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 18:45:31 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

typedef struct		s_opt {
    int     p;
    int     q;
    int     r;
    int     s;
    t_list  *str;
    t_list  *files;
}		            t_opt;

u_int64_t           build_msg(char **pmsg, char *msg, u_int64_t len, int invert);


#endif
