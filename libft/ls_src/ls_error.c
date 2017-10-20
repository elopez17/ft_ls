/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:14:32 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/19 18:27:24 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_ill_opt(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1\
] [file ...]\n");
	exit(1);
}
