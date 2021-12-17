/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_files_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:23:21 by lmariott          #+#    #+#             */
/*   Updated: 2021/03/19 11:24:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int         md5_file(char *file)
{
    int fd;

    if ((fd = open(file, O_RDONLY)) <= 0)
    {
        ft_putstr_fd("Cannot open ", 2);
        ft_putendl_fd(file, 2);
        return (-1);
    }
    if (!(md5_by_fd(fd)))
        return (0);
    close(fd);
    return (1);
}

int         md5_run_files_loop(void)
{
    t_md5   *md5;
    t_list  *head;

    md5 = get_md5();
    head = md5->opt->files;
    while (head)
    {
        if (!md5->opt->q)
        {
            ft_putstr("MD5(");
            ft_putstr((char*)head->content);
            ft_putstr(") = ");
        }
        if (!md5_file(head->content))
            return (0);
        if (md5->opt->q)
        {
            ft_putstr(" ");
            ft_putstr((char*)head->content);
        }
        write(1, "\n", 1);
        head = head->next;
    }
    return (1);
}
