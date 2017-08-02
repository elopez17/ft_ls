/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:08:10 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:08:38 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_color4(const char **format, va_list *ap)
{
	if (**format == 'p')
	{
		*format += 2;
		return (write(1, "\x1b[35m", 5));
	}
	if (**format == 't')
	{
		*format += 2;
		return (write(1, "\x1b[36m", 5));
	}
	if (**format == 'w')
	{
		*format += 2;
		return (write(1, "\x1b[37m", 5));
	}
	return (pf_invalid_spec(ap));
}

static int	pf_color3(const char **format, va_list *ap)
{
	if (**format == 'r')
	{
		*format += 2;
		return (write(1, "\x1b[31m", 5));
	}
	if (**format == 'g')
	{
		*format += 2;
		return (write(1, "\x1b[32m", 5));
	}
	if (**format == 'y')
	{
		*format += 2;
		return (write(1, "\x1b[33m", 5));
	}
	if (**format == 'b')
	{
		*format += 2;
		return (write(1, "\x1b[34m", 5));
	}
	return (pf_color4(format, ap));
}

static int	pf_color2(const char **format, va_list *ap)
{
	if (**format == 'B')
	{
		*format += 2;
		return (write(1, "\x1b[34;01m", 8));
	}
	if (**format == 'P')
	{
		*format += 2;
		return (write(1, "\x1b[35;01m", 8));
	}
	if (**format == 'T')
	{
		*format += 2;
		return (write(1, "\x1b[36;01m", 8));
	}
	if (**format == 'W')
	{
		*format += 2;
		return (write(1, "\x1b[37;01m", 8));
	}
	return (pf_color3(format, ap));
}

int			pf_color(const char **format, va_list *ap)
{
	if (*(++*format + 2) != '}')
		pf_invalid_spec(ap);
	if (**format == 'n' || **format == 'N')
	{
		*format += 2;
		return (write(1, "\x1b[0m", 4));
	}
	if (**format == 'R')
	{
		*format += 2;
		return (write(1, "\x1b[31;01m", 8));
	}
	if (**format == 'G')
	{
		*format += 2;
		return (write(1, "\x1b[32;01m", 8));
	}
	if (**format == 'Y')
	{
		*format += 2;
		return (write(1, "\x1b[33;01m", 8));
	}
	return (pf_color2(format, ap));
}
