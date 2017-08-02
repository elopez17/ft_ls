/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wint_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 00:04:22 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/01 14:17:13 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_width(wint_t cval, t_flags *flag, int len)
{
	int printed;

	printed = 0;
	if (flag->zero)
		while (len--)
			printed += write(1, "0", 1);
	else if (flag->left_adj == 0)
		while (len--)
			printed += write(1, " ", 1);
	printed += ft_putwint(cval);
	if (flag->left_adj)
		while (len--)
			printed += write(1, " ", 1);
	return (printed);
}

int			pf_wint_t(t_flags *flag, va_list *ap)
{
	t_spec u;

	u.c_val = va_arg(*ap, wint_t);
	if (flag->precision)
		return (pf_invalid_prec(ap));
	if (flag->width > (int)ft_wcharlen(&u.c_val))
	{
		return (print_width(u.c_val, flag, \
					flag->width - ft_wcharlen(&u.c_val)));
	}
	return (ft_putwint(u.c_val));
}
