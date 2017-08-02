/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_invalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:41:48 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 12:53:47 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_invalid_spec(va_list *ap)
{
	va_end(*ap);
	ft_putendl("\n\x1b[31;01mError:\x1b[0m Invalid Specifier");
	exit(EXIT_FAILURE);
	return (0);
}

int		pf_invalid_flag(va_list *ap)
{
	va_end(*ap);
	ft_putendl("\n\x1b[31;01mError:\x1b[0m Invalid flag for given specifier");
	exit(EXIT_FAILURE);
	return (0);
}

int		pf_invalid_prec(va_list *ap)
{
	va_end(*ap);
	ft_putendl("\n\x1b[31;01mError:\x1b[0m precision is \
invalid with 'c' / 'C'");
	exit(EXIT_FAILURE);
	return (0);
}
