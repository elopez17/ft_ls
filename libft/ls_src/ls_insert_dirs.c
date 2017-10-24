/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_dirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 13:24:12 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/24 11:25:43 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		frontbacksplit(t_dirs *source, \
		t_dirs **frontref, t_dirs **backref)
{
	t_dirs *fast;
	t_dirs *slow;

	if (source == NULL || source->next == NULL)
	{
		*frontref = source;
		*backref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontref = source;
		*backref = slow->next;
		slow->next = NULL;
	}
}

static t_dirs	*sortedmerge(t_dirs *a, t_dirs *b)
{
	t_dirs *result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->path, b->path) <= 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next);
	}
	return (result);
}

static void		ls_mergesort(t_dirs **headref)
{
	t_dirs *head;
	t_dirs *a;
	t_dirs *b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontbacksplit(head, &a, &b);
	ls_mergesort(&a);
	ls_mergesort(&b);
	*headref = sortedmerge(a, b);
}

static void		reverse_lst(t_dirs **lst)
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

void			ls_insert_dirs(t_dirs *new, t_dirs **dir, unsigned int rev)
{
	t_dirs *tmp;

	ft_printf("insertfunc\n");
	ls_mergesort(&new);
	ft_printf("after insertfunc\n");
	tmp = (*dir)->next;
	if (rev && new->next != NULL)
		reverse_lst(&new);
	(*dir)->next = new;
	new = (*dir);
	while (new->next != NULL)
		new = new->next;
	new->next = tmp;
}
