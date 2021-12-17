/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_s_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:25:28 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/08 11:59:16 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

int             sha256_run_s_loop(void)
{
    t_list  *head;
    unsigned char        *hash;

    head = get_sha256()->opt->str;
    while (head)
    {
        if (!get_sha256()->opt->q)
        {
            ft_putstr("MD5(\"");
            ft_putstr((char*)head->content);
            ft_putstr("\") = ");
        }
        if (!(hash = sha256((char*)head->content,
            ft_strlen((char*)head->content))))
            return (0);
        ft_puthexlen(hash, 32);
        if (get_sha256()->opt->q)
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
