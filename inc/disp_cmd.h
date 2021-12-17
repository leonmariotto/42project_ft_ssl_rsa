/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:09:20 by lmariott          #+#    #+#             */
/*   Updated: 2021/12/14 13:15:04 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISP_CMD_H
# define DISP_CMD_H

typedef struct          s_func {
    const char      *cmd;
    int             (*f)(char **av, int ac);
}                       t_func;

t_func      g_disp_cmd[] = {
    {"md5", run_md5},
    {"sha256", run_sha256},
    {"base64", run_base64},
    {"des", run_des_ecb},
    {"des-ecb", run_des_ecb},
    {"des-cbc", run_des_cbc},
    {"des3", run_des3_cbc},
    {"des3-ecb", run_des3_ecb},
    {"des3-cbc", run_des3_cbc},
    {"genrsa", run_genrsa},
    {"rsa", run_rsa},
    {"rsautl", run_rsautl},
};

#endif
