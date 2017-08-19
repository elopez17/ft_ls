/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:26:09 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/15 20:31:03 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>

typedef struct	s_option
{
	unsigned int	a : 1;
	unsigned int	t : 1;
	unsigned int	r;
	unsigned int	l : 1;
	unsigned int	R : 1;
}				t_option;

typedef struct	s_dirs
{
	char			*path;
	char			*files;
	struct s_dirs	*next;
}				t_dirs;

void	ft_p_exit(char *s);
char	*ls_get_files(char *files, char *file, t_option *opt);
char	*ls_get_dirs(char *path, char *dir);
void	ls_insert_dirs(t_dirs *new, t_dirs **dir, unsigned int rev);
char	**ls_sort_files(char *files, char *dir_path, t_option *opt);
void	ls_swap_files(char **s1, char **s2);
time_t	ls_get_time(char *dir_path, char *file);
void	ls_print_data(char **files, char *path, t_option *opt);
void	ls_print_perm(int octal);
void	ls_free_2d(char ***arr_2d);
void	ls_free_mem(t_dirs **head, t_option **opt);

#endif
