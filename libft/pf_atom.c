/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_atom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:14:49 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:23:50 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_atom_0_9(char c)
{
	if (c == '0')
		return (write(1, "_____  ", 7));
	else if (c == '1')
		return (write(1, ".____  ", 7));
	else if (c == '2')
		return (write(1, "..___  ", 7));
	else if (c == '3')
		return (write(1, "...__  ", 7));
	else if (c == '4')
		return (write(1, "...._  ", 7));
	else if (c == '5')
		return (write(1, ".....  ", 7));
	else if (c == '6')
		return (write(1, "_....  ", 7));
	else if (c == '7')
		return (write(1, "__...  ", 7));
	else if (c == '8')
		return (write(1, "___..  ", 7));
	else
		return (write(1, "____.  ", 7));
}

static int	pf_atom_o_z(char c)
{
	if (c == 'o' || c == 'O')
		return (write(1, "___  ", 5));
	else if (c == 'p' || c == 'P')
		return (write(1, ".__.  ", 6));
	else if (c == 'q' || c == 'Q')
		return (write(1, "__._  ", 6));
	else if (c == 'r' || c == 'R')
		return (write(1, "._.  ", 5));
	else if (c == 's' || c == 'S')
		return (write(1, "...  ", 5));
	else if (c == 't' || c == 'T')
		return (write(1, "_  ", 3));
	else if (c == 'u' || c == 'U')
		return (write(1, ".._  ", 5));
	else if (c == 'v' || c == 'V')
		return (write(1, "..._  ", 6));
	else if (c == 'w' || c == 'W')
		return (write(1, ".__  ", 5));
	else if (c == 'x' || c == 'X')
		return (write(1, "_.._  ", 6));
	else if (c == 'y' || c == 'Y')
		return (write(1, "_.__  ", 6));
	else
		return (write(1, "__..  ", 6));
}

static int	pf_atom_c_n(char c)
{
	if (c == 'c' || c == 'C')
		return (write(1, "_._.  ", 6));
	else if (c == 'd' || c == 'D')
		return (write(1, "_..  ", 5));
	else if (c == 'e' || c == 'E')
		return (write(1, ".  ", 3));
	else if (c == 'f' || c == 'F')
		return (write(1, ".._.  ", 6));
	else if (c == 'g' || c == 'G')
		return (write(1, "__.  ", 5));
	else if (c == 'h' || c == 'H')
		return (write(1, "....  ", 6));
	else if (c == 'i' || c == 'I')
		return (write(1, "..  ", 4));
	else if (c == 'j' || c == 'J')
		return (write(1, ".___  ", 6));
	else if (c == 'k' || c == 'K')
		return (write(1, "_._  ", 5));
	else if (c == 'l' || c == 'L')
		return (write(1, "._..  ", 6));
	else if (c == 'm' || c == 'M')
		return (write(1, "__  ", 4));
	else
		return (write(1, "_.  ", 4));
}

int			pf_atom(va_list *ap)
{
	int		len;
	char	c;
	t_spec	u;

	len = 0;
	u.sval = va_arg(*ap, char*);
	while ((c = *u.sval) != '\0')
	{
		if (c == ' ')
			len += write(1, "   ", 3);
		else if (c == 'a' || c == 'A')
			len += write(1, "._  ", 4);
		else if (c == 'b' || c == 'B')
			len += write(1, "_...  ", 6);
		else if ((c >= 'c' && c <= 'n') || (c >= 'C' && c <= 'N'))
			len += pf_atom_c_n(c);
		else if ((c >= 'o' && c <= 'z') || (c >= 'O' && c <= 'Z'))
			len += pf_atom_o_z(c);
		else if (c >= '0' && c <= '9')
			len += pf_atom_0_9(c);
		else if (c != '.' && c != '_')
			len += write(1, &c, 1);
		++u.sval;
	}
	return (len);
}
