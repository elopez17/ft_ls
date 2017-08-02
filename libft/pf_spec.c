/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:33:29 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:33:31 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_spec_di(t_flags *flag, va_list *ap)
{
	flag->zero = (flag->precision == 1) ? 0 : flag->zero;
	if (flag->alter)
		return (pf_invalid_flag(ap));
	else if (flag->l)
		return (pf_long(flag, ap));
	else if (flag->ll)
		return (pf_long_long(flag, ap));
	else if (flag->j)
		return (pf_intmax_t(flag, ap));
	else if (flag->z)
		return (pf_ulong_long(flag, ap, 'd'));
	else
		return (pf_int(flag, ap));
}

int		pf_spec_cs(t_flags *flag, va_list *ap, char c)
{
	if (flag->alter | flag->space | flag->sign)
		return (pf_invalid_flag(ap));
	if ((c == 'c' && flag->l) || c == 'C')
		return (pf_wint_t(flag, ap));
	else if ((c == 's' && flag->l) || c == 'S')
		return (pf_wchar_t(flag, ap));
	else if (c == 'c')
		return (pf_char(flag, ap));
	else if (c == 's')
		return (pf_str(flag, ap));
	return (0);
}

int		pf_spec_ouxz(t_flags *flag, va_list *ap, char c)
{
	flag->zero = (flag->precision == 1) ? 0 : flag->zero;
	if (flag->space || flag->sign || ((c == 'u' || c == 'U') && flag->alter))
		return (pf_invalid_flag(ap));
	if (flag->j)
		return (pf_uintmax_t(flag, ap, c));
	return (pf_ulong_long(flag, ap, c));
}
