/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:12:30 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:13:50 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_prefix(t_flags *flag, char **result)
{
	if (flag->sign)
		*result = ft_strmerge(ft_strdup("+"), *result);
	else if (flag->space)
		*result = ft_strmerge(ft_strdup(" "), *result);
}

static void	set_decimal(t_flags *flag, char **result)
{
	char *temp;

	if (flag->precision && flag->precision_num < 6)
	{
		flag->precision_num -= 6;
		temp = ft_strsub(*result, 0, ft_strlen(*result) + flag->precision_num);
		ft_strdel(result);
		*result = temp;
	}
	if (flag->alter == 0 && *(*result + ft_strlen(*result) - 1) == '.')
		*(*result + ft_strlen(*result) - 1) = '\0';
}

static int	print_width(t_flags *flag, char **result)
{
	int len;

	len = 0;
	if (flag->left_adj == 0)
		while (flag->width > (int)ft_strlen(*result))
		{
			if (flag->zero)
				*result = ft_strmerge(ft_strdup("0"), *result);
			else
				*result = ft_strmerge(ft_strdup(" "), *result);
		}
	else
		while (flag->width > (int)ft_strlen(*result))
			*result = ft_strmerge(*result, ft_strdup(" "));
	len += write(1, *result, ft_strlen(*result));
	return (len);
}

int			pf_float(t_flags *flag, va_list *ap)
{
	t_spec	u;
	double	dec_part;
	char	*int_part;
	char	*result;

	u.lfval = va_arg(*ap, double);
	int_part = ft_lltoa((long long)u.lfval);
	if (*int_part == '0' && u.lfval < 0.0)
		int_part = ft_strmerge(ft_strdup("-"), int_part);
	dec_part = (u.lfval - (long long)u.lfval) * 1000000.0;
	dec_part *= (dec_part < 0.0) ? -1 : 1;
	result = ft_strmerge(int_part, ft_strdup("."));
	if (ft_strlen(u.sval = ft_lltoa((long long)dec_part)) < 6)
		while (ft_strlen(u.sval) != 6)
			u.sval = ft_strmerge(ft_strdup("0"), u.sval);
	result = ft_strmerge(result, u.sval);
	if (result[0] != '-' && (flag->sign | flag->space))
		add_prefix(flag, &result);
	set_decimal(flag, &result);
	if (flag->width > (int)ft_strlen(result))
		u.dval = print_width(flag, &result);
	else
		u.dval = write(1, result, ft_strlen(result));
	ft_strdel(&result);
	return (u.dval);
}
