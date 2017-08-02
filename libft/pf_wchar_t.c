/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wchar_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:39:32 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 14:11:39 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prec(wchar_t *s, t_flags *flag)
{
	int i;

	i = 0;
	while (flag->precision_num-- && s[i])
		ft_putwint(s[i++]);
}

static void	print_width(wchar_t *s, t_flags *flag)
{
	int len;
	int i;

	i = 0;
	if (flag->precision && (size_t)flag->precision_num < ft_wcharlen(s))
		len = flag->width - flag->precision_num;
	else
		len = flag->width - ft_wcharlen(s);
	if (flag->zero)
		while (len--)
			ft_putchar('0');
	else if (flag->left_adj == 0)
		while (len--)
			ft_putchar(' ');
	if (flag->precision && (size_t)flag->precision_num < ft_wcharlen(s))
		while (flag->precision_num-- && s[i])
			ft_putwint(s[i++]);
	else
		while (s[i])
			ft_putwint(s[i++]);
	if (flag->left_adj)
		while (len--)
			ft_putchar(' ');
}

int			pf_wchar_t(t_flags *flag, va_list *ap)
{
	t_spec	u;
	int		len;
	int		i;

	i = 0;
	u.s_val = va_arg(*ap, wchar_t*);
	len = ft_wcharlen(u.s_val);
	if (flag->width > len)
	{
		print_width(u.s_val, flag);
		return (flag->width);
	}
	else if (flag->precision)
	{
		print_prec(u.s_val, flag);
		return (flag->precision_num);
	}
	while (u.s_val[i])
		ft_putwint(u.s_val[i++]);
	return (len);
}
