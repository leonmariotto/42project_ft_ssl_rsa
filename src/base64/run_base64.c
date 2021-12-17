/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_base64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 10:52:16 by lmariott          #+#    #+#             */
/*   Updated: 2021/08/28 18:21:26 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <stdio.h>

int         base64_parse_opt(char **av, int *i)
{
    t_base64   *base64;

    if (!(base64 = get_base64()))
        return (0);
    if (av[*i][1] == 'd')
        base64->opt->d = 1;
    else if (av[*i][1] == 'e')
        base64->opt->d = 0;
    else if (av[*i][1] == 'i')
    {
        (*i)++;
        if ((base64->opt->input = ft_openfile(av[*i], 0)) < 0)
            return (0);
    }
    else if (av[*i][1] == 'o')
    {
        (*i)++;
        if ((base64->opt->output = ft_openfile(av[*i], 1)) < 0)
            return (0);
    }
    else
    {
        ft_putstr_fd("Unrecognized flag : ", 2);
        ft_putendl_fd(av[*i], 2);
        return (0);
    }
    return (1);
}

int         base64_get_opt(char **av, int ac)
{
    int i;

    if (ac <= 2)
        return (1);
    i = 2;
    while (i < ac)
    {
        if (av[i][0] == '-')
        {
            if (!base64_parse_opt(av, &i))
                return (0); // Error, print usage, free and go
        }
        else
            return (0); // Error, print usage, free and go
        ++i;
    }
    return (1);
}

void        print_base64(int fd, char  *output, int len)
{
    int     i;

    i = 0;
    if (len < 64)
       write(fd, output, len);
    else
    {
        while (i < len / 64)
        {
           write(fd, output + i * 64, 64);
           write(fd, "\n", 1);
           i++; 
        }
        write(fd, output + i * 64, len - i * 64);
    }
    write(fd, "\n", 1);
}

int         run_base64(char **av, int ac)
{
    char            *ptr;
    unsigned char   *input;
    int             len;

    if (!base64_get_opt(av, ac))
    {
        free(get_base64()->opt);
        free(get_base64());
        return (0);
    }
    if ((len = ft_readfd(get_base64()->opt->input, (char **)&input)) <= 0)
        return (0);
    if (!(base64((void **)&ptr, input, &len, get_base64()->opt->d)))
    {
        free(input);
        return (0);    
    }
    if (!get_base64()->opt->d)
        print_base64(get_base64()->opt->output, ptr, len);
    else
        write(get_base64()->opt->output, ptr, len);
    free(input);
    free(ptr);
    exit_base64();
    return (1);
}
