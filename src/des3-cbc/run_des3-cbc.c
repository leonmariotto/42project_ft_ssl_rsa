/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_des3-cbc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:33:36 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 19:24:24 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void            exit_des3_cbc(void)
{
    close(get_des()->opt->output);
    close(get_des()->opt->input);
    free(get_des()->keyring);
    if (get_des()->opt->passwd)
        free(get_des()->opt->passwd);
    if (get_des()->salt)
        free(get_des()->salt);
    if (get_des()->iv)
        free(get_des()->iv);
    if (get_des()->key)
        free(get_des()->key);
    free(get_des()->opt);
    free(get_des());
}

int             run_des3_cbc(void **av, int ac)
{
    unsigned char   *input;
    char            *ptr;
    char            *b64_ptr;
    int             len;

    if (!des_get_opt((char **)av, ac))
    {
        free(get_des()->opt);
        free(get_des());
        return (0);
    }
    if ((len = ft_readfd(get_des()->opt->input, (char **)&input)) <= 0)
    {
	exit_des3_cbc();
        return (0);
    }
    if (get_des()->opt->d && get_des()->opt->a)
    {
        if (!(base64((void **)&b64_ptr, input, &len, 1)))
        {
            free(input);
	    exit_des3_cbc();
            return (0);
        }
        free(input);
        input = (unsigned char *)b64_ptr;
    }
    if (!(des3_cbc((void **)&ptr, input, &len, get_des()->opt->d)))
    {
        free(input);
	exit_des3_cbc();
        return (0);
    }
    if (!get_des()->opt->d && get_des()->opt->a)
    {
        if (!(base64((void **)&b64_ptr, (unsigned char*)ptr, &len, 0)))
        {
            free(ptr);
            free(input);
	    exit_des3_cbc();
            return (0);
        }
        free(ptr);
        ptr = b64_ptr;
    }
    write(get_des()->opt->output, ptr, len);
    free(ptr);
    free(input);
    exit_des3_cbc();
    return (0);
}

