/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pathiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 11:21:53 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/18 19:35:43 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_pathiter(t_option *opt, char *files, char **path)
{
	int i;
	int	end;

	end = -1;
	i = 0;
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
		ft_printf(i == 0 && !*files ? (path[1] != 0 ?\
					"%s:\n": "") : "\n%s:\n", path[i]);
		ls_path(opt, "", path[i]);
		opt->r ? --i : ++i;
	}
}
