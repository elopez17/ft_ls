/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:54:53 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/23 12:54:52 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	ls_part(char **files, int start, int end)
{
	int	partition_i;
	int	i;

	partition_i = start;
	i = start;
	while (i < end)
	{
		if (ft_strcmp(files[end], files[i]) > 0)
		{
			ls_swap_files(&(files[i]), &(files[partition_i]));
			partition_i++;
		}
		++i;
	}
	ls_swap_files(&(files[partition_i]), &(files[end]));
	return (partition_i);
}

void		ls_sort(char **files, int start, int end)
{
	int partition_i;

	if (start < end)
	{
		partition_i = ls_part(files, start, end);
		ls_sort(files, start, partition_i - 1);
		ls_sort(files, partition_i + 1, end);
	}
}

static int	timepart(char **files, int start, int end, char *dir_path)
{
	time_t		pivot;
	time_t		file_t;
	int			partition_i;
	int			i;

	pivot = ls_get_time(dir_path, files[end]);
	partition_i = start;
	i = start;
	while (i < end)
	{
		file_t = ls_get_time(dir_path, files[i]);
		if (file_t > pivot)
		{
			ls_swap_files(&(files[i]), &(files[partition_i]));
			partition_i++;
		}
		else if (file_t == pivot && ft_strcmp(files[end], files[i]) > 0)
		{
			ls_swap_files(&(files[i]), &(files[partition_i]));
			partition_i++;
		}
		++i;
	}
	ls_swap_files(&(files[partition_i]), &(files[end]));
	return (partition_i);
}

void		timesort(char **files, int start, int end, char *dir_path)
{
	int partition_i;

	if (start < end)
	{
		partition_i = timepart(files, start, end, dir_path);
		timesort(files, start, partition_i - 1, dir_path);
		timesort(files, partition_i + 1, end, dir_path);
	}
}

char		**ls_sort_files(t_dirs *d, char *files, char *d_path, t_option *opt)
{
	char	**file_arr;
	int		i;
	int		end;
	int		slen;

	i = 0;
	end = 0;
	file_arr = ft_strsplit(files, ' ');
	while (file_arr[end + 1])
		if ((slen = ft_strlen(file_arr[end++])) > d->width)
			d->width = slen;
	if ((slen = ft_strlen(file_arr[end])) > d->width)
		d->width = slen;
	if (opt->t == 0)
	{
		while (!opt->a && file_arr[i] != NULL && file_arr[i][0] == '.')
			++i;
		ls_sort(file_arr, (i > 2) ? 2 : i, end);
	}
	else
		timesort(file_arr, 0, end, d_path);
	if (opt->r)
		opt->r = end;
	return (file_arr);
}
