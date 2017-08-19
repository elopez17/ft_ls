/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_perm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 12:52:31 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/11 14:48:32 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	file_type(int octal)
{
	if ((octal & S_IFREG) == S_IFREG)
		ft_putchar('-');
	else if ((octal & S_IFDIR) == S_IFDIR)
		ft_putchar('d');
	else if ((octal & S_IFLNK) == S_IFLNK)
		ft_putchar('l');
	else if ((octal & S_IFIFO) == S_IFIFO)
		ft_putchar('p');
	else if ((octal & S_IFCHR) == S_IFCHR)
		ft_putchar('c');
	else if ((octal & S_IFBLK) == S_IFBLK)
		ft_putchar('b');
	else if ((octal & S_IFSOCK) == S_IFSOCK)
		ft_putchar('s');
	else if ((octal & S_IFWHT) == S_IFWHT)
		ft_putchar('w');
}

static void	permissions(int octal)
{
	if (octal & 0444)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (octal & 0222)
		ft_putchar('w');
	else
		ft_putchar('-');
	if ((octal & 0111) && !(octal & 07000))
		ft_putchar('x');
	else if (!(octal & 07000))
		ft_putchar('-');
}

void		ls_print_perm(int octal)
{
	file_type(octal);
	permissions(octal & 04700);
	if (octal & 04000)
		(octal & 0100) ? ft_putchar('s') : ft_putchar('S');
	permissions(octal & 02070);
	if (octal & 02000)
		(octal & 010) ? ft_putchar('s') : ft_putchar('S');
	permissions(octal & 01007);
	if (octal & 01000)
		(octal & 01) ? ft_putchar('t') : ft_putchar('T');
}
