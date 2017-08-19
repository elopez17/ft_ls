/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:31:37 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/04 12:04:34 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*ls_get_files(char *files, char *file, t_option *opt)
{
	if (opt->a == 0 && (ft_memcmp(file, ".", ft_strlen(file) == 0) ||\
ft_memcmp(file, "..", ft_strlen(file) == 0)))
	{
		return (files);
	}
	files = ft_strmer(files, ft_strdup(file));
	files = ft_strmer(files, ft_strdup(" "));
	return (files);
}
