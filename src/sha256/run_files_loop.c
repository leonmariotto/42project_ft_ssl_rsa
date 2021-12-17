/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_files_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:27:10 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 12:38:54 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int         sha256_file(char *file)
{
    int fd;

    if ((fd = open(file, O_RDONLY)) <= 0)
    {
        ft_putstr_fd("Cannot open ", 2);
        ft_putendl_fd(file, 2);
        return (0);
    }
    if (!(sha256_by_fd(fd)))
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int         sha256_run_files_loop(void)
{
    t_sha256   *sha256;
    t_list  *head;

    sha256 = get_sha256();
    head = sha256->opt->files;
    while (head)
    {
        if (!sha256->opt->q)
        {
            ft_putstr("SHA256(");
            ft_putstr((char*)head->content);
            ft_putstr(") = ");
        }
        if (!sha256_file(head->content))
            return (0);
        if (sha256->opt->q)
        {
            ft_putstr(" ");
            ft_putstr((char*)head->content);
        }
        write(1, "\n", 1);
        head = head->next;
    }
    return (1);
}
