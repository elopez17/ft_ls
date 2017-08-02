/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:27:48 by elopez            #+#    #+#             */
/*   Updated: 2017/07/20 16:36:28 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_len(t_flags *flag, int num)
{
	int len;
	int prefix;

	len = 1;
	prefix = num;
	if (num < 0)
	{
		num *= -1;
		++len;
	}
	else if (num >= 0 && (flag->sign || flag->space))
		++len;
	prefix = (prefix < 0 || flag->sign || flag->space) ? 1 : 0;
	while (num /= 10)
		++len;
	if (flag->width > len && flag->precision == 0)
		return (flag->width);
	else if (flag->width > len && flag->width > flag->precision_num + prefix)
		return (flag->width);
	if (flag->precision_num + prefix > len &&
			flag->precision_num + prefix >= flag->width && flag->precision)
		return (flag->precision_num + prefix);
	return (len);
}

static void	print_prec(char **s, int len)
{
	int prefix;

	prefix = (ft_isdigit(**s)) ? 0 : 1;
	if (prefix)
		ft_putchar(*(*s)++);
	while (len--)
		ft_putchar('0');
	ft_putstr(*s);
	return ;
}

static void	print_width(char **s, t_flags *flag, int len)
{
	int i;

	i = (ft_isdigit(**s)) ? ft_strlen(*s) : ft_strlen(*s) + 1;
	if (flag->left_adj)
	{
		if (ft_isdigit(**s) == 0)
			ft_putchar(*(*s)++);
		if (flag->precision && flag->precision_num > i)
			while (flag->precision_num > i++ && len--)
				ft_putchar('0');
		ft_putstr(*s);
		while (len--)
			ft_putchar(' ');
		return ;
	}
	if (flag->zero && ft_isdigit(**s) == 0)
		ft_putchar(*(*s)++);
	while (flag->zero && len--)
		ft_putchar('0');
	while (flag->zero == 0 && len--)
		if (flag->precision && len + 1 == flag->precision_num - i)
			ft_putchar('0');
		else
			ft_putchar(' ');
	ft_putstr(*s);
}

int			pf_int(t_flags *flag, va_list *ap)
{
	t_spec	u;
	int		len;
	char	*s;
	int		sign;

	sign = 0;
	u.dval = va_arg(*ap, int);
	s = ft_itoa(u.dval);
	len = get_len(flag, u.dval);
	if (u.dval < 0 || (flag->sign | flag->space))
		sign = 1;
	if ((flag->space | flag->sign) && u.dval >= 0)
		s = (flag->space) ? ft_strmerge(ft_strdup(" "), s) :
			ft_strmerge(ft_strdup("+"), s);
	if (len > (int)ft_strlen(s) && flag->precision_num + sign == len
			&& flag->precision)
		print_prec(&s, len - ft_strlen(s));
	else if (len > (int)ft_strlen(s) && flag->width == len)
		print_width(&s, flag, len - ft_strlen(s));
	else
		ft_putstr(s);
	return (len);
}
