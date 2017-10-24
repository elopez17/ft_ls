/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pathiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 11:21:53 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/24 13:57:49 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_pathiter(t_option *opt, char *files, char **path)
{
	int i;
	int	end;

	end = -1;
	if (*files != '\0' || *path == 0)
	{
		opt->files = (*files != '\0') ? 1 : opt->files;
		ls_path(opt, files, ".");
		opt->files = 0;
	}
	while (path[++end] != 0)
		;
	if (opt->t)
		timesort(path, 0, end != 0 ? --end : end, ".");
	else
		ls_sort(path, 0, end != 0 ? --end : end);
	i = opt->r ? end : 0;
	while (i >= 0 && path[i] != 0)
	{
		if (i == 0 && !*files)
			ft_printf(path[1] != 0 || opt->files ? "%s:\n" : "", path[i]);
		else
			ft_printf("\n%s:\n", path[i]);
		ls_path(opt, "", path[opt->r ? i-- : i++]);
	}
}
