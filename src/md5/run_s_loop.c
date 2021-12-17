/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_s_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:05:19 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 11:17:32 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int             md5_run_s_loop(void)
{
    t_list          *head;
    unsigned char    *hash;

    head = get_md5()->opt->str;
    while (head)
    {
        if (!get_md5()->opt->q)
        {
            ft_putstr("MD5(\"");
            ft_putstr((char*)head->content);
            ft_putstr("\") = ");
        }
        if (!(hash = md5((char*)head->content, ft_strlen((char*)head->content))))
            return (0);
        ft_puthexlen(hash, 8);
        free(hash);
        if (get_md5()->opt->q)
        {
            ft_putstr(" \"");
            ft_putstr((char*)head->content);
            ft_putstr("\"");
        }
        write(1, "\n", 1);
        head = head->next;
    }
    return (1);
}
