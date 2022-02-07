/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 20:06:32 by lmariott          #+#    #+#             */
/*   Updated: 2022/02/07 14:17:44 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void        print_usage(void)
{
    ft_putendl("usage: ./ft_ssl command [command opts] [command args]");
    ft_putendl("Standard commands:");
    ft_putendl("rsa");
    ft_putendl("genrsa");
    ft_putendl("rsautl");
    ft_putstr("\n");
    ft_putendl("Message Digest commands:");
    ft_putstr("md5\n");
    ft_putstr("sha256\n");
    ft_putstr("\n");
    ft_putendl("Cipher commands:");
    ft_putstr("base64\n");
    ft_putstr("des-ecb\n");
    ft_putstr("des-cbc\n");
    ft_putstr("des3-ecb\n");
    ft_putstr("des3-cbc\n");
    ft_putstr("\n");
}

int			main(int ac, char **av)
{
    if (ac < 2)
    {
        print_usage();
        return (1); // print_usage
    }
    if (!exec_cmd(av, ac))
        return (1);
    return (0);
}
