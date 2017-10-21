/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free_heap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:01:49 by elopez            #+#    #+#             */
/*   Updated: 2017/10/20 09:48:40 by eLopez           ###   ########.fr       */
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

void	ls_free_all(char **files, char **dirs, char ***path, t_option **opt)
{
	ft_strdel(files);
	ft_strdel(dirs);
	free_2d(path);
	ft_memdel((void**)opt);
}

void	free_2d(char ***arr_2d)
{
	int i;

	i = 0;
	while ((*arr_2d)[i])
		ft_strdel(&(*arr_2d)[i++]);
	free(*arr_2d);
}
