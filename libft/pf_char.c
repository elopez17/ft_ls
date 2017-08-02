/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:06:26 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:07:55 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_width(unsigned char cval, t_flags *flag, int len)
{
	if (flag->zero)
		while (len--)
			ft_putchar('0');
	else if (flag->left_adj == 0)
		while (len--)
			ft_putchar(' ');
	ft_putchar(cval);
	if (flag->left_adj)
		while (len--)
			ft_putchar(' ');
}

int			pf_char(t_flags *flag, va_list *ap)
{
	t_spec u;

	u.cval = va_arg(*ap, int);
	if (flag->precision)
		return (pf_invalid_prec(ap));
	if (flag->width > 1)
	{
		print_width(u.cval, flag, flag->width - 1);
		return (flag->width);
	}
	return (write(1, &(u.cval), 1));
}
