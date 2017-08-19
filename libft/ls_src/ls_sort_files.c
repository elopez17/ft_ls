/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:54:53 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/16 23:11:34 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	default_sort(char **files, int insert)
{
	int	i;
	int k;

	k = 0;
	i = insert;
	if (insert == 0)
		return ;
	while (files[i] && files[++i])
	{
		if (ft_strcmp(files[insert], files[i]) > 0)
		{
			ls_swap_files(&(files[insert]), &(files[i]));
			++insert;
			i = insert;
		}
	}
}
static int	partition(char **files, int start, int end, char *dir_path)
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
		if (file_t >= pivot)
		{
			ls_swap_files(&(files[i]), &(files[partition_i]));
			partition_i++;
		}
		++i;
	}
	ls_swap_files(&(files[partition_i]), &(files[end]));
	return (partition_i);
}

static void	quicksort(char **files, int start, int end, char *dir_path)
{
	int partition_i;

	if (start < end)
	{
		partition_i = partition(files, start, end, dir_path);
		quicksort(files, start, partition_i - 1, dir_path);
		quicksort(files, partition_i + 1, end, dir_path);
	}
}

char		**ls_sort_files(char *files, char *dir_path, t_option *opt)
{
	char	**file_arr;
	int		i;
	int		end;

	i = 0;
	end = 0;
	file_arr = ft_strsplit(files, ' ');
	while (file_arr[end + 1])
		++end;
	if (opt->t == 0)
	{
		while (file_arr[i] != NULL && file_arr[i][0] == '.')
			++i;
		default_sort(file_arr, (end == 0) ? 0 : 2);
		default_sort(file_arr, i);
	}
	else
		quicksort(file_arr, 0, end, dir_path);
	if (opt->r)
		opt->r = end;
	return (file_arr);
}
