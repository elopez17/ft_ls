/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_swap_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 20:04:36 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/05 22:16:00 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_swap_files(char **s1, char **s2)
{
	char *temp;

	temp = *s2;
	*s2 = *s1;
	*s1 = temp;
}
