/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:01:18 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:02:07 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_pow(long long x, long long y)
{
	long long cpy;

	cpy = x;
	if (x == 0 && y <= 0)
		return (-1);
	if (y == 0)
		return (1);
	while (--y)
		x *= cpy;
	return (x);
}
