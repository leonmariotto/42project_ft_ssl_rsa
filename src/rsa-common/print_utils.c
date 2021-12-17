/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:57:29 by leon              #+#    #+#             */
/*   Updated: 2021/12/17 17:15:21 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "des.h"
#include "base64.h"

void	ft_putulong_fd(uint64_t n, int fd)
{
	if (n > 9)
		ft_putulong_fd(n / 10, fd);
	ft_putchar_fd('0' + (n % 10), fd);
}

void	ft_putu_fd(uint32_t n, int fd)
{
	if (n > 9)
		ft_putu_fd(n / 10, fd);
	ft_putchar_fd('0' + (n % 10), fd);
}

void			myprintulong(char *str, uint64_t nb)
{
	write(2, str, ft_strlen(str));
	ft_putulong_fd(nb, 2);
	write(2, "\n", 1);
}
void			myprintu(char *str, uint64_t nb)
{
	write(2, str, ft_strlen(str));
	ft_putulong_fd(nb, 2);
	write(2, "\n", 1);
}

void			print_obj(t_asn_obj *obj)
{
	uint64_t	i;
	char		base[16];

	ft_memcpy(base, "0123456789abcdef", 16);
	i = 0;
	if (!obj || obj->len == 0)
		return ; // Should never reach this
	while (i < obj->len)
	{
		ft_putchar_fd(base[obj->content[i] / 16], 2);
		ft_putchar_fd(base[obj->content[i] % 16], 2);
//		ft_putchar_fd(':', 2);
		i++;
	}
	write(2, "\n", 1);
}

void			print_text(t_list *top, t_rsa_opt opt)
{
	t_list *head;
	//int i = 0;

	head = top;
	//while (head)
	//{
	//	i++;
	//	fprintf(stderr, "i = %d\n", i);
	//	print_obj(head->content);
	//	head = head->next;
	//}
	head = head->next; // skip version
	ft_putstr_fd("modulus : ", 2);
	if (!head)
		fprintf(stderr, "unexpected!\n");
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("publicExponent : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	if (opt.pubin)
		return ;
	head = head->next;
	ft_putstr_fd("privateExponent : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("prime1 : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("prime2 : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("exponent1 : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("exponent2 : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
	ft_putstr_fd("coefficient : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
	head = head->next;
}

void			print_modulus(t_list *top)
{
	t_list *head;

	head = top;
	head = head->next; // skip version
	ft_putstr_fd("modulus : ", 2);
	print_obj(head->content);
	write(2, "\n", 1);
}


//int			print_text(t_rsa_key key, bool pub)
//{
//	if (!pub)
//	{
//		myprintulong("modulus : ", key.modulus);
//		myprintu("publicExponent: ", key.publicExponent);
//		myprintulong("privateExponent: ", key.privateExponent);
//		myprintu("prime1: ", key.prime1);
//		myprintu("prime2: ", key.prime2);
//		myprintu("exponent1: ", key.exponent1);
//		myprintu("exponent2: ", key.exponent2);
//		myprintu("coefficient: ", key.coefficient);
//	}
//	if (pub)
//	{
//		myprintulong("modulus : ", key.modulus);
//		myprintu("publicExponent: ", key.publicExponent);
//	}
//	return (1);
//}
