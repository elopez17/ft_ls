#include <ft_ls.h>

void	ls_free_mem(t_dirs **head, t_option **opt)
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
	ft_memdel((void**)opt);
}

void	ls_free_2d(char ***arr_2d)
{
	int i;

	i = 0;
	while ((*arr_2d)[i])
		ft_strdel(&(*arr_2d)[i++]);
	free(*arr_2d);
}
