/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:03:07 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/07 18:18:33 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdio.h>

int         parse_opt(char **av, int *i)
{
    t_md5   *md5;

    md5 = get_md5();
    if (av[*i][1] == 's')
    {
        md5->opt->s += 1;
        (*i)++;
        ft_lstpush(&md5->opt->str, ft_lstnew(av[*i], ft_strlen(av[*i]) + 1));
    }
    else if (av[*i][1] == 'q')
        md5->opt->q = 1;
    else if (av[*i][1] == 'r')
        md5->opt->r = 1;
    else if (av[*i][1] == 'p')
        md5->opt->p = 1;
    else
    {
        ft_putstr_fd("Unrecognized flag : ", 2);
        ft_putendl_fd(av[*i], 2);
        return (0);
    }
    return (1);
}

int         file_loop(char **av, int i)
{
    t_md5       *md5;
    t_list      *new;

    md5 = get_md5();
    while (av[i])
    {
        if (!(new = ft_lstnew(av[i], ft_strlen(av[i]) + 1)))
            return (0);
        ft_lstpush(&md5->opt->files, new);
        i++;
    }
    return (1);
}

int         get_opt(char **av, int ac)
{
    int i;

    if (ac <= 2)
        return (1);
    i = 2;
    while (i < ac)
    {
        if (av[i][0] == '-')
        {
            if (!parse_opt(av, &i))
                return (0); // Error, print usage, free and go
        }
        else
            return (file_loop(av, i)); // Le reste est des fichiers. t_list ?
        ++i;
    }
    return (1);
}

int         run_md5(char **av, int ac)
{
    t_md5   *smd5;

    if (!(smd5 = get_md5()))
        return (0);
    if (!(get_opt(av, ac)))
        return (0);
    if ((!smd5->opt->files && !smd5->opt->s) || smd5->opt->p)
    {
        if (!(md5_by_fd(0)))
            return (0);
        write(1, "\n", 1);
    }
    if (smd5->opt->s)
        if (!(md5_run_s_loop()))
            return (0);
    if (smd5->opt->files)
        if (!(md5_run_files_loop()))
            return (0);
    md5_exit();
    return (1);
}
