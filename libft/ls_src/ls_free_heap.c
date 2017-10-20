/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free_heap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:01:49 by elopez            #+#    #+#             */
/*   Updated: 2017/10/19 18:01:56 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_free_lst(t_dirs **head)
{
	t_dirs *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_strdel(&tmp->path);
		ft_strdel(&tmp->files);
		ft_memdel((void**)&tmp);
	}
	ft_memdel((void**)head);
}

void	free_2d(char ***arr_2d)
{
	int i;

	i = 0;
	while ((*arr_2d)[i])
		ft_strdel(&(*arr_2d)[i++]);
	free(*arr_2d);
}
