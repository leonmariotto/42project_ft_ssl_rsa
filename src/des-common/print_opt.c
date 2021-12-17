/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:55:48 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:00:52 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void            print_opt(void)
{
    ft_putendl("./ft_ssl des*");
    ft_putendl("-h : display this help");
    ft_putendl("-a : encrypt/decrypt in base64 depending of the mode");
    ft_putendl("-e : encryption (default)");
    ft_putendl("-d : decryption");
    ft_putendl("-pbkdf2 : use password key derivation function v2 (default for des3-*)");
    ft_putendl("-iter nb : nb of iteration (default 10)");
    ft_putendl("-i file : input file (default stdin)");
    ft_putendl("-o file : output file (default stdout)");
    ft_putendl("-p password : (in hex) password used for key derivation");
    ft_putendl("-s salt : (in hex) salt used for key derivation");
    ft_putendl("-k key : (in hex) key (no pbkdf)\n	WARNING:cbc mode need iv");
    ft_putendl("-v init_vector : (in hex) init vector for cbc mode (no pbkdf)");

}
