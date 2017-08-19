/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_uintmax_t.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:42:05 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:48:29 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_len(t_flags *flag, uintmax_t num)
{
	int			len;
	uintmax_t	prefix;

	len = 1;
	prefix = num;
	if (flag->sign | flag->space)
		++len;
	prefix = (flag->sign | flag->space) ? 1 : 0;
	while (num /= 10)
		++len;
	if (flag->width > len && flag->precision == 0)
		return (flag->width);
	else if (flag->width > len && flag->width > \
			flag->precision_num + (int)prefix)
		return (flag->width);
	if (flag->precision_num + (int)prefix > len && flag->precision_num \
			+ (int)prefix >= flag->width && flag->precision)
		return (flag->precision_num + (int)prefix);
	return (len);
}

static void		print_prec(char **s, int len)
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

static void		print_width(char **s, t_flags *flag, int len)
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

int				pf_uintmax_t(t_flags *flag, va_list *ap, char c)
{
	t_spec	u;
	int		len;
	char	*s;
	int		sign;

	sign = 0;
	u.uimax = va_arg(*ap, uintmax_t);
	if (c == 'o' || c == 'O')
		s = pf_o_uintmax(flag, u.uimax);
	else if (c == 'x' || c == 'X')
		s = pf_x_uintmax(flag, u.uimax, c);
	else
		s = ft_uimttoa(u.uimax);
	len = get_len(flag, u.uimax);
	if ((sign = (flag->sign | flag->space) ? 1 : 0))
		s = (flag->space) ? ft_strmerge(ft_strdup(" "), s) : \
			ft_strmerge(ft_strdup("+"), s);
	if (len > (int)ft_strlen(s) && flag->precision_num + sign == len \
			&& flag->precision)
		print_prec(&s, len - ft_strlen(s));
	else if (len > (int)ft_strlen(s) && flag->width == len)
		print_width(&s, flag, len - ft_strlen(s));
	else
		ft_putstr(s);
	return (len);
}