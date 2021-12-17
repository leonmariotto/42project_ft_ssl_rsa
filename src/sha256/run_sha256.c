/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:04:03 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/07 22:43:30 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <stdio.h>

int         sha256_parse_opt(char **av, int *i)
{
    t_sha256   *sha256;

    sha256 = get_sha256();
    if (av[*i][1] == 's')
    {
        sha256->opt->s += 1;
        (*i)++;
        ft_lstpush(&sha256->opt->str, ft_lstnew(av[*i], ft_strlen(av[*i]) + 1));
    }
    else if (av[*i][1] == 'q')
        sha256->opt->q = 1;
    else if (av[*i][1] == 'r')
        sha256->opt->r = 1;
    else if (av[*i][1] == 'p')
        sha256->opt->p = 1;
    else
    {
        ft_putstr_fd("Unrecognized flag : ", 2);
        ft_putendl_fd(av[*i], 2);
        return (0);
    }
    return (1);
}

int         sha256_file_loop(char **av, int i)
{
    t_sha256       *sha256;
    t_list      *new;

    sha256 = get_sha256();
    while (av[i])
    {
        if (!(new = ft_lstnew(av[i], ft_strlen(av[i]) + 1)))
            return (0);
        ft_lstpush(&sha256->opt->files, new);
        i++;
    }
    return (1);
}

int         sha256_get_opt(char **av, int ac)
{
    int i;

    if (ac <= 2)
        return (1);
    i = 2;
    while (i < ac)
    {
        if (av[i][0] == '-')
        {
            if (!sha256_parse_opt(av, &i))
                return (0); // Error, print usage, free and go
        }
        else
            return (sha256_file_loop(av, i)); // Le reste est des fichiers. t_list ?
        ++i;
    }
    return (1);
}

int         run_sha256(char **av, int ac)
{
    t_sha256   *ssha256;

    //fprintf(stderr, "%s:%d\n", __func__, __LINE__);
    if (!(ssha256 = get_sha256()))
        return (0);
    if (!(sha256_get_opt(av, ac)))
        return (sha256_exit());
    //fprintf(stderr, "%s:%d\n", __func__, __LINE__);
    if ((!ssha256->opt->files && !ssha256->opt->s) || ssha256->opt->p)
    {
        if (!(sha256_by_fd(0)))
            return (sha256_exit());
        write(1, "\n", 1);
    }
    //fprintf(stderr, "%s:%d\n", __func__, __LINE__);
    if (ssha256->opt->s)
        if (!(sha256_run_s_loop()))
            return (sha256_exit());
    //fprintf(stderr, "%s:%d\n", __func__, __LINE__);
    if (ssha256->opt->files)
        if (!(sha256_run_files_loop()))
            return (sha256_exit());
    //fprintf(stderr, "%s:%d\n", __func__, __LINE__);
    sha256_exit();
    return (1);
}
