/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:26:09 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/02 14:39:38 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <libft.h>

typedef struct	s_option
{
	unsigned int	a : 1;
	unsigned int	t : 1;
	unsigned int	r : 1;
	unsigned int	l : 1;
	unsigned int	R : 1;
}				t_option;

typedef struct	s_dirs
{
	char			*path;
	struct s_dirs	*next;
}				t_dirs;

#endif
