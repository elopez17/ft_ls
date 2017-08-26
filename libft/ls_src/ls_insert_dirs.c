/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_dirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 13:24:12 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/25 21:53:15 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	reverse_lst(t_dirs **lst)
{
	t_dirs *current;
	t_dirs *prev;
	t_dirs *next;

	current = (*lst);
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		if (next == NULL)
			break ;
		current = next;
	}
	*lst = current;
}

void		ls_insert_dirs(t_dirs *new, t_dirs **dir, unsigned int rev)
{
	t_dirs *tmp;

	tmp = (*dir)->next;
	if (rev && new->next != NULL)
		reverse_lst(&new);
	(*dir)->next = new;
	new = (*dir);
	while (new->next != NULL)
		new = new->next;
	new->next = tmp;
}
