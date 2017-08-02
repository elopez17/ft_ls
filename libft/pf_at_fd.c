/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_at_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:04:46 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:05:41 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_invalid_fd(va_list *ap)
{
	va_end(*ap);
	ft_putendl("\n\x1b[31;01mError:\x1b[0m Invalid file descriptor");
	exit(EXIT_FAILURE);
}

int			pf_at_fd(va_list *ap)
{
	int		fd;
	t_spec	u;

	fd = va_arg(*ap, int);
	if (fd < 0)
		pf_invalid_fd(ap);
	u.sval = va_arg(*ap, char*);
	ft_putstr_fd(u.sval, fd);
	return (ft_strlen(u.sval));
}
