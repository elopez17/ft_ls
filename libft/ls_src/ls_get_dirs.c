/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:31:37 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/04 12:22:33 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*ls_get_dirs(char *path, char *dir)
{
	char	*new_path;

	new_path = ft_strmer(ft_strdup("/"), ft_strdup(dir));
	new_path = ft_strmer(ft_strdup(path), new_path);
	return (new_path);
}
