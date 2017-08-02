/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 00:06:56 by eLopez            #+#    #+#             */
/*   Updated: 2017/07/21 15:13:41 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	pf_conv_flags(const char **format)
{
	t_flags	flag;

	ft_bzero(&flag, sizeof(flag));
	while (*++*format == ' ' || **format == '#' || **format == '-' ||\
			**format == '+' || **format == '0')
	{
		if (**format == '#')
			flag.alter = 1;
		else if (**format == '-')
			flag.left_adj = 1;
		else if (**format == '0')
			flag.zero = 1;
		else if (**format == '+')
			flag.sign = 1;
		else if (**format == ' ')
			flag.space = 1;
	}
	if (flag.left_adj & flag.zero)
		flag.zero = 0;
	if (flag.sign & flag.space)
		flag.space = 0;
	return (flag);
}

void	pf_conv_width(const char **format, t_flags *flag, va_list *ap)
{
	int num;

	num = 0;
	if (ft_isdigit(**format))
		while (ft_isdigit(**format))
		{
			num = num * 10 + ((**format) - '0');
			(*format)++;
		}
	else if (**format == '*')
	{
		num = va_arg(*ap, int);
		(*format)++;
	}
	flag->width = num;
}

void	pf_conv_precision(const char **format, t_flags *flag, va_list *ap)
{
	int num;

	num = 0;
	if (**format == '.')
	{
		if (*++*format != '-')
			flag->precision = 1;
		else
			(*format)++;
		if (ft_isdigit(**format))
			while (ft_isdigit(**format))
			{
				num = num * 10 + ((**format) - '0');
				(*format)++;
			}
		else if (**format == '*')
		{
			num = va_arg(*ap, int);
			(*format)++;
		}
		flag->precision_num = num;
	}
}

void	pf_conv_length(const char **format, t_flags *flag)
{
	if (**format == 'h')
		flag->h = 1;
	if (**format == 'l')
		flag->l = 1;
	if (**format == 'j')
		flag->j = 1;
	if (**format == 'z')
		flag->z = 1;
	if (flag->h | flag->l | flag->j | flag->z)
		(*format)++;
	if (**format == 'h' && flag->h == 1)
	{
		flag->hh = 1;
		flag->h = 0;
	}
	if (**format == 'l' && flag->l == 1)
	{
		flag->ll = 1;
		flag->l = 0;
	}
	if (flag->hh | flag->ll)
		(*format)++;
}
