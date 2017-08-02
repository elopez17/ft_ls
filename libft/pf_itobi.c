/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itobi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:16:06 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:16:28 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_itobi(t_flags *flag, va_list *ap)
{
	t_spec				u;
	unsigned long long	mask;
	int					len;

	mask = 0xf000000000000000;
	len = 0;
	u.ullval = va_arg(*ap, unsigned long long);
	while (!(mask & u.ullval) && mask)
		mask >>= 4;
	mask &= 0x8888888888888888;
	while (mask)
	{
		if (mask & u.ullval)
			len += write(1, "1", 1);
		else
			len += write(1, "0", 1);
		if (flag->alter && (mask & 0x1111111111111110))
			len += write(1, "-", 1);
		mask >>= 1;
	}
	if (u.ullval == 0)
		return (write(1, "0", 1));
	return (len);
}
