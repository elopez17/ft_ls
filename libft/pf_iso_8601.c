/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_iso_8601.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:14:33 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:14:35 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_iso_8601(va_list *ap)
{
	t_spec	u;
	int		date;

	date = 3;
	while (date--)
	{
		u.dval = va_arg(*ap, int);
		if (u.dval < 10)
			ft_putchar('0');
		ft_putnbr(u.dval);
		if (date > 0)
			ft_putchar('-');
	}
	return (10);
}
