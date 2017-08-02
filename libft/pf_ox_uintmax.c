/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ox_uintmax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:35:19 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:35:21 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*hex_letter(uintmax_t hex, char c)
{
	char *s;

	if (hex < 10)
		s = ft_uimttoa(hex);
	else if (hex == 10)
		s = (c == 'x') ? ft_strdup("a") : ft_strdup("A");
	else if (hex == 11)
		s = (c == 'x') ? ft_strdup("b") : ft_strdup("B");
	else if (hex == 12)
		s = (c == 'x') ? ft_strdup("c") : ft_strdup("C");
	else if (hex == 13)
		s = (c == 'x') ? ft_strdup("d") : ft_strdup("D");
	else if (hex == 14)
		s = (c == 'x') ? ft_strdup("e") : ft_strdup("E");
	else
		s = (c == 'x') ? ft_strdup("f") : ft_strdup("F");
	return (s);
}

char		*pf_x_uintmax(t_flags *flag, uintmax_t dec, char c)
{
	char		*s;
	int			i;
	uintmax_t	arr[15];

	i = 0;
	s = ft_strnew(1);
	while ((dec / 16) > 15)
	{
		arr[i++] = dec;
		dec /= 16;
	}
	s = ft_strmerge(s, hex_letter(dec / 16, c));
	s = ft_strmerge(s, hex_letter(dec % 16, c));
	while (--i >= 0)
		s = ft_strmerge(s, hex_letter(arr[i] % 16, c));
	if (flag->alter && (c == 'x' || c == 'X'))
		s = (c == 'x') ? ft_strmerge(ft_strdup("0x"), s) : \
			ft_strmerge(ft_strdup("0X"), s);
	return (s);
}

char		*pf_o_uintmax(t_flags *flag, uintmax_t dec)
{
	char		*s;
	int			i;
	uintmax_t	arr[20];
	uintmax_t	octal;

	i = 0;
	while ((dec / 8) > 7)
	{
		arr[i++] = dec;
		dec /= 8;
	}
	octal = dec / 8;
	octal = (octal * 10) + (dec % 8);
	while (--i >= 0)
		octal = (octal * 10) + (arr[i] % 8);
	s = ft_uimttoa(octal);
	if (flag->alter)
		if (flag->precision == 0 || flag->precision_num < (int)ft_strlen(s) + 1)
		{
			flag->precision_num = ft_strlen(s) + 1;
			flag->precision = 1;
		}
	return (s);
}
