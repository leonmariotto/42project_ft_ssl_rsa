/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:29:16 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/14 13:15:43 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

/*
** Le programme ft_ssl est simplement un dispatcher vers plusieurs
** fonctions de hachage ou autre.
** Avoir un tableau, un dispatcher, transmettre les options a la
** commandes correspondante et c'est marre
*/

int		run_md5(char **av, int ac);
int		run_sha256(char **av, int ac);
int		run_base64(char **av, int ac);
int		run_des_ecb(char **av, int ac);
int		run_des3_ecb(char **av, int ac);
int		run_des3_cbc(char **av, int ac);
int		run_des_cbc(char **av, int ac);
int		run_genrsa(char **av, int ac);
int		run_rsa(char **av, int ac);
int		run_rsautl(char **av, int ac);
int		exec_cmd(char **av, int ac);

#endif
