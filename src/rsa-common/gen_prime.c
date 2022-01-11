/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:12:35 by leon              #+#    #+#             */
/*   Updated: 2021/12/20 22:28:35 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

uint64_t		add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	a = a % mod;
	b = b % mod;
	if (a >= mod - b)
		return (a - (mod - b));
	return (a + b);
}

uint64_t		mult_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	uint64_t res;

	res = 0;
	while (b > 0)
	{
		if (b & 1)
			res = add_mod(res, a, mod);
		a = add_mod(a, a, mod);
		b = b >> 1;
	}
	return (res);
}

uint64_t		pow_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	uint64_t res;

	res = 1;
	a = a % mod;
	if (a == 0)
		return (0);
	while (b > 0)
	{
		if (b & 1)
			res = mult_mod(res, a, mod);
		b = b >> 1;
		a = mult_mod(a, a, mod);
	}
	return (res);
}

bool		millerrabin(uint32_t n, uint32_t d, int randomfd)
{
	u_int64_t	rand;
	u_int64_t	x;

	if (!get_random((void*)&rand, 8, randomfd))
		return (0);
	rand = (rand % (n - 4)) + 2;
	x = pow_mod(rand, d, n);
	if (x == 1 || x == n - 1)
		return (true);
	while (d != n - 1)
	{
		x = pow_mod(x, x, n);
		d = d << 1;
		if (x == 1)
			return (false);
		if (x == n - 1)
			return (true);
	}
	return (false);
}

bool				ft_isprime(uint32_t nb, uint32_t iter, int randomfd, bool verb)
{
	uint32_t	d;

	if (nb <= 1 || nb == 4)
		return (false);
	if (nb <= 3)
		return (true);
	d = nb - 1;
	while (d & 0)
		d = d >> 1;
	while (iter > 0)
	{
		if (millerrabin(nb, d, randomfd) == 0)
			return (false);
		if (verb)
			write(2, "+", 1);
		iter--;
	}
	return (true);
}

uint32_t			gen_prime(int randomfd, bool verb)
{
	uint32_t	r;

	if (!get_random(&r, 4, randomfd))
	       return (0);
	while (!ft_isprime(r, 34, randomfd, verb))
	{
		if (!get_random(&r, 4, randomfd))
			return (0);
		if (verb)
			write(2, ".", 1);
	}
	if (verb)
		write(2, "\n", 1);
	return (r);
}
