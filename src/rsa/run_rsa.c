/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rsa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:08:00 by leon              #+#    #+#             */
/*   Updated: 2021/12/20 22:32:55 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

// OK il faut refaire touuuuuuuuuuuut rsa_process pour au4il fonctionne avec la liste chaine
int			check_key(t_list *top)
{
	t_list *head ;
	uint64_t	privateExponent;
	uint32_t	publicExponent;
	uint32_t	tmp;
	uint32_t	prime1;
	uint32_t	prime2;

	head = top;
	head = head->next;
	head = head->next;
	if (((t_asn_obj*)head->content)->len > 4)
		err_return("publicExponent: Invalid lenght");
	ft_memcpy(&publicExponent, ((t_asn_obj*)head->content)->content, ((t_asn_obj*)head->content)->len);
	head = head->next;
	if (((t_asn_obj*)head->content)->len > 8)
		err_return("privateExponent: Invalid lenght");
	ft_memcpy(&privateExponent, ((t_asn_obj*)head->content)->content, ((t_asn_obj*)head->content)->len);
	head = head->next;
	if (((t_asn_obj*)head->content)->len > 4)
		err_return("prime1: Invalid lenght");
	ft_memcpy(&prime1, ((t_asn_obj*)head->content)->content, ((t_asn_obj*)head->content)->len);
	head = head->next;
	if (((t_asn_obj*)head->content)->len > 4)
		err_return("prime2: Invalid lenght");
	ft_memcpy(&prime2, ((t_asn_obj*)head->content)->content, ((t_asn_obj*)head->content)->len);

	tmp = lcm(prime1 - 1, prime2 - 1);
	if (mult_mod(privateExponent, publicExponent, tmp) != 1)
		err_return("rsa: check failed, key invalid");
	else
		ft_putendl_fd("Check done, key OK", 2);
	return (1);

}

int			rsa_process(t_list *top, t_rsa_opt opt)
{
	if (opt.check)
	{
		if (opt.pubin)
			err_return("rsa: check opt is for private key");
		if (!check_key(top))
			return (0);
		//tmp = lcm(key.prime1 - 1, key.prime2 - 1);
		//if (mult_mod(key.privateExponent, key.publicExponent, tmp) != 1)
		//	err_return("rsa: check failed, key invalid");
		//else
		//	ft_putendl_fd("Check done, key OK", 2);
	}
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
	t_rsa_opt	opt;
	t_list		*top;
	char		*input;

	top = NULL;
	ft_bzero(&opt, sizeof(opt));
	if (!(rsa_getopt(&opt, av, ac)))
		return (err_return("rsa: get_opt failed\n"));
	if (!(len = ft_readfd(opt.infd, &input)))
		return (err_return("rsa: unable to read file\n"));
	if (!(rsa_extract_key(&input, &len, opt.pubin, opt.passin, &top)))
		return (0);
	if (!rsa_process(top, opt))
		return (0);
	free(input);
	return (1);
}
