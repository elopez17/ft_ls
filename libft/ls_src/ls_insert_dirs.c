/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_dirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 13:24:12 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/23 20:52:18 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
	
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
and return the two lists using the reference parameters.
If the length is odd, the extra node should go in the front list.
Uses the fast/slow pointer strategy. */

static void		frontbacksplit(t_dirs *source, \
		t_dirs **frontref, t_dirs **backref)
{
	t_dirs *fast;
	t_dirs *slow;

	if (source == NULL || source->next == NULL)
	{
		/* length < 2 cases */
		*frontref = source;
		*backref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
/* 'slow' is before the midpoint in the list,
   so split it in two at that point. */
		*frontref = source;
		*backref = slow->next;
		slow->next = NULL;
	}
}

static t_dirs	*sortedmerge(t_dirs *a, t_dirs *b)
{
	t_dirs *result;

	/* Base cases */
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	/* Pick either a or b, and recur */
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
	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
		return ;
	/* Split head into 'a' and 'b' sublists */
	frontbacksplit(head, &a, &b); 
	/* Recursively sort the sublists */
	ls_mergesort(&a);
	ls_mergesort(&b);
	/* answer = merge the two sorted lists together */
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

	ls_mergesort(&new);
	tmp = (*dir)->next;
	if (rev && new->next != NULL)
		reverse_lst(&new);
	(*dir)->next = new;
	new = (*dir);
	while (new->next != NULL)
		new = new->next;
	new->next = tmp;
}
