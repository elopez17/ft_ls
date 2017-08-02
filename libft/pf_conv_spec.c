/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 12:48:16 by eLopez            #+#    #+#             */
/*   Updated: 2017/07/21 13:36:31 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_specifier(const char **format, t_flags *flag, va_list *ap)
{
	char c;

	if ((c = **format) == '%')
		return (write(1, "%", 1));
	if (c == 'c' || c == 's' || c == 'C' || c == 'S')
		return (pf_spec_cs(flag, ap, c));
	if (c == 'd' || c == 'i' || c == 'D')
	{
		flag->l = (c == 'D') ? 1 : flag->l;
		return (pf_spec_di(flag, ap));
	}
	if (c == 'u' || c == 'o' || c == 'x' || c == 'X' || c == 'O' || c == 'U')
		return (pf_spec_ouxz(flag, ap, c));
	if (c == 'p')
	{
		flag->alter = 1;
		return (pf_spec_ouxz(flag, ap, 'x'));
	}
	return (pf_conv_specif_2(format, flag, ap));
}

int		pf_conv_specif_2(const char **format, t_flags *flag, va_list *ap)
{
	char c;

	if ((c = **format) == '{')
		return (pf_color(format, ap));
	if (c == '@')
		return (pf_at_fd(ap));
	if (c == 'b')
		return (pf_itobi(flag, ap));
	if (c == 'm')
		return (pf_atom(ap));
	if (c == 'f' || c == 'F')
		return (pf_float(flag, ap));
	if (c == 'k')
		return (pf_iso_8601(ap));
	return (pf_invalid_spec(ap));
}
