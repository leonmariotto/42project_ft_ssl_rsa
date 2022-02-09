/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rsa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:08:00 by leon              #+#    #+#             */
/*   Updated: 2022/02/09 22:34:03 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int			rsa_process(t_list *top, t_rsa_opt opt)
{
	if (opt.text)
		print_text(top, opt);
	if (opt.modulus)
		print_modulus(top);
	if (!opt.noout)
	{
		if (!(rsa_print_out(top, opt)))
			return (0);
		//if (!(rsa_print_out(key, opt)))
		//	return (0);
	}
	return (1);
}



int			run_rsa(void **av, int ac)
{
	int		len;
	int		len_cpy;
	t_rsa_opt	opt;
	t_list		*top;
	char		*input;
	char		*cpy;
	t_rsa_key	key;
	int		randomfd;

	top = NULL;
	ft_bzero(&opt, sizeof(opt));
	if (!(rsa_getopt(&opt, av, ac)))
		return (err_return("rsa: get_opt failed\n"));
	if (!(len = ft_readfd(opt.infd, &input)))
		return (err_return("rsa: unable to read file\n"));
	if (opt.check)
	{
		if (opt.pubin)
			return (err_return("-check is only for private key"));
		cpy = ft_memdup(input, len);
		len_cpy = len;
		if (!(rsa_extract_key_struct(&cpy, &len_cpy,
				opt.pubin, opt.passin, &key)))
			return (0);
		randomfd = open_randomfd(NULL);
		if (!ft_isprime(key.prime1, 34, randomfd, 1))
			return (err_return("p is not prime"));
		write(2, "\n", 1);
		if (!ft_isprime(key.prime2, 34, randomfd, 1))
			return (err_return("q is not prime"));
		write(2, "\n", 1);
		if (key.modulus != ((uint64_t)(key.prime1) * (uint64_t)(key.prime2)))
			return (err_return("modulus is not p * q"));
		close(randomfd);
		free(cpy);
		ft_putendl_fd("Check done, key OK", 2);
	}
	if (!(rsa_extract_key(&input, &len, opt.pubin, opt.passin, &top)))
		return (0);
	if (!rsa_process(top, opt))
		return (0);
	free(input);
	return (1);
}
