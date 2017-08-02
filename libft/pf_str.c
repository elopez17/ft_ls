/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:36:27 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:36:29 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prec(char *s, t_flags *flag)
{
	int i;

	i = 0;
	while (flag->precision_num-- && s[i])
		ft_putchar(s[i++]);
}

static void	print_width(char *s, t_flags *flag)
{
	int len;
	int i;

	i = 0;
	if (flag->precision && flag->precision_num < (int)ft_strlen(s))
		len = flag->width - flag->precision_num;
	else
		len = flag->width - ft_strlen(s);
	if (flag->zero)
		while (len--)
			ft_putchar('0');
	else if (flag->left_adj == 0)
		while (len--)
			ft_putchar(' ');
	if (flag->precision && flag->precision_num < (int)ft_strlen(s))
		while (flag->precision_num-- && s[i])
			ft_putchar(s[i++]);
	else
		ft_putstr(s);
	if (flag->left_adj)
		while (len--)
			ft_putchar(' ');
}

int			pf_str(t_flags *flag, va_list *ap)
{
	t_spec	u;
	int		len;

	u.sval = va_arg(*ap, char*);
	len = ft_strlen(u.sval);
	if (flag->precision && flag->precision_num < len)
		len = flag->precision_num;
	if (flag->width > len)
	{
		print_width(u.sval, flag);
		return (flag->width);
	}
	else if (flag->precision)
	{
		print_prec(u.sval, flag);
		return (flag->precision_num);
	}
	ft_putstr(u.sval);
	return (len);
}
