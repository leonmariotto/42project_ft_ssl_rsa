/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 19:36:25 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/15 20:45:16 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <fcntl.h>

// open "/dev/random" read close

int                 gen_salt(unsigned char **ptr)
{
    u_int8_t        	*salt;
    int			fd;
    char		buf[512];
    
    if (!(salt = (u_int8_t*)ft_memalloc(8)))
        return (0);
    if ((fd = open("/dev/random", O_RDONLY)) < 0)
	return (0);
    if ((read(fd, buf, 512)) < 0)
	    err_return("gen_salt: read random");
    close(fd);
    ft_memcpy(salt, buf, 8);
    *ptr = salt;
    return (1);
}
