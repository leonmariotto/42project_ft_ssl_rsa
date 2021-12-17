/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_paswd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 19:34:09 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:27:23 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

// TODO verify
// Est-ce la bonne fonction a utiliser ?
int                 ask_paswd(char **ptr)
{
    char    *passwd;
    char    *verif;

    if (!(passwd = getpass("enter password:"))
            || !(verif = getpass("re-enter password:"))
            || ft_strcmp(passwd, verif))
    {
        ft_putendl_fd("Error: passwd input", 2);
        return (0);
    }
    if (!(*ptr = (char*)ft_strdup(passwd)))
        return (0);
    return (1);
}
