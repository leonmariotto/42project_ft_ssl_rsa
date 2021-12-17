/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   euclide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:07:50 by leon              #+#    #+#             */
/*   Updated: 2021/12/15 21:07:58 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int64_t		gcd_extended(int64_t a, int64_t b, int64_t *u, int64_t *v)
{
    int64_t x1;
    int64_t y1;
    int64_t gcd;

    if (a == 0)
    {
        *u = 0;
        *v = 1;
        return b;
    }

    gcd = gcd_extended(b % a, a, &x1, &y1);

    *u = y1 - (b/a) * x1;
    *v = x1;

    return gcd;
}

uint32_t			euclide(uint32_t a, uint32_t b)
{
	uint32_t tmp;

	while (b)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a);
}

uint32_t	gcd(uint32_t a, uint32_t b)
{
	return (euclide(a, b));
}

uint64_t	lcm(uint64_t a, uint64_t b)
{
	return ((a / euclide(a, b)) * b);
}
