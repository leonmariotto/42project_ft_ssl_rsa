/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:27:30 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/06 18:29:20 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int             ft_openfile(char *file, int mod)
{
    int fd;

    if (!mod)
    {
        if ((fd = open(file, O_RDONLY )) <= 0)
        {
            ft_putstr_fd("Cannot open ", 2);
            ft_putendl_fd(file, 2);
            return (-1);
        }
    }
    else
    {
        if ((fd = open(file,  O_CREAT | O_TRUNC | O_RDWR,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) <= 0)
        {
            ft_putstr_fd("Cannot open ", 2);
            ft_putendl_fd(file, 2);
            return (-1);
        }
    }
    return (fd);
}
