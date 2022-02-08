/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_getopt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:40:50 by lmariott          #+#    #+#             */
/*   Updated: 2022/02/08 19:03:52 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int         des_parse_opt(char **av, int *i)
{
    t_des   *des;

    des = get_des();
    if (av[*i][1] == 'h')
    {
        print_opt();
        return (0);
    }
    else if (av[*i][1] == 'd')
        des->opt->d = 1;
    else if (av[*i][1] == 'e')
        des->opt->d = 0;
    else if (av[*i][1] == 'a')
        des->opt->a = 1;
    else if (!ft_strcmp(&av[*i][1], "pbkdf2"))
        des->opt->pbkdf2 = 1;
    else if (!ft_strcmp(&av[*i][1], "iter"))
    {
        (*i)++;
        if (ft_atoi(av[*i]) <= 0)
            return (0);
        des->opt->iter = ft_atoi(av[*i]);
    }
    else if (av[*i][1] == 'p' && av[*i][2] == 0)
    {
        (*i)++;
        if (!(des->opt->passwd = ft_strdup(av[*i])))
            return (0);
    }
    else if (av[*i][1] == 's')
    {
        (*i)++;
        if (!(des->salt = (u_int8_t*)ft_ahextovbin(av[*i], 8)))
            return (0);
    }
    else if (av[*i][1] == 'v')
    {
        (*i)++;
        if (!(des->iv = (u_int8_t*)ft_ahextovbin(av[*i], 8)))
            return (0);
        des->opt->v = 1;
    }
    else if (av[*i][1] == 'k')
    {
        (*i)++;
        if (!(des->key = (u_int8_t*)ft_ahextovbin(av[*i], 24)))
            return (0);
    }
    else if (av[*i][1] == 'i')
    {
        (*i)++;
        if ((des->opt->input = ft_openfile(av[*i], 0)) < 0)
            return (0);
    }
    else if (av[*i][1] == 'o')
    {
        (*i)++;
        if ((des->opt->output = ft_openfile(av[*i], 1)) < 0)
            return (0);
    }
    else if (!ft_strcmp(av[*i], "-nosalt"))
    {
	(*i)++;
        des->opt->nosalt = 1;
    }
    else
    {
        ft_putstr_fd("Unrecognized flag : ", 2);
        ft_putendl_fd(av[*i], 2);
        return (0);
    }
    return (1);
}

int         des_get_opt(char **av, int ac)
{
    int i;

    if (ac <= 2)
        return (1);
    i = 2;
    while (i < ac)
    {
        if (av[i][0] == '-')
        {
            if (!des_parse_opt(av, &i))
                return (0);
        }
        else
            return (0);
        ++i;
    }
    return (1);
}
