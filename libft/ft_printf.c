/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:40:34 by elopez            #+#    #+#             */
/*   Updated: 2017/07/21 15:16:51 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_analyze(va_list *ap, const char *format)
{
	int		len;
	t_flags	flag;

	len = 0;
	len = ft_putcstr(format, '%');
	while ((format = ft_strchr(format, '%')))
	{
		flag = pf_conv_flags(&format);
		pf_conv_width(&format, &flag, ap);
		pf_conv_precision(&format, &flag, ap);
		pf_conv_length(&format, &flag);
		len += pf_conv_specifier(&format, &flag, ap);
		len += ft_putcstr(++format, '%');
	}
	return (len);
}

int			ft_printf(const char *format, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	if (format)
	{
		va_start(ap, format);
		len = pf_analyze(&ap, format);
		va_end(ap);
	}
	return (len);
}
