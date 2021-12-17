/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:00:35 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/14 18:38:05 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "disp_cmd.h"
#include <stdio.h>

void        cmd_usage(char *unknow_cmd)
{
    ft_putstr("./ft_ssl: Error: '");
    ft_putstr(unknow_cmd);
    ft_putstr("' is an invalid command.\n\n");
    ft_putendl("Standard commands:");
    ft_putendl("rsa\n");
    ft_putendl("rsautl\n");
    ft_putendl("genrsa\n");
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

int         exec_cmd(char **av, int ac)
{
    unsigned int i;

    i = 0;
	while (i < sizeof(g_disp_cmd) / sizeof(t_func))
    {
        if (!ft_strcmp(av[1], g_disp_cmd[i].cmd))
            return (g_disp_cmd[i].f(av, ac));
        ++i;
    }
    cmd_usage(av[1]);
    return (0);
}
