/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 19:21:31 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/19 11:46:18 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

time_t	ls_get_time(char *dir_path, char *file)
{
	char		*path;
	struct stat	attr;

	path = ft_strjoin(dir_path, "/");
	path = ft_strmer(path, ft_strdup(file));
	lstat(path, &attr);
	ft_strdel(&path);
	return (attr.st_mtime);
}
