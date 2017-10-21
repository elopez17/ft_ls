/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:26:09 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/20 09:50:41 by eLopez           ###   ########.fr       */
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
# include <errno.h>
# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define MEMCHECK(x) if (x) ft_p_exit("malloc")

typedef struct	s_option
{
	unsigned int	a : 1;
	unsigned int	t : 1;
	unsigned int	r;
	unsigned int	l : 1;
	unsigned int	R : 1;
	unsigned int	one : 1;
	unsigned int	files : 1;
}				t_option;

typedef struct	s_dirs
{
	char			*path;
	char			*files;
	int				width;
	struct s_dirs	*next;
}				t_dirs;

void	ft_p_exit(char *s);
void	ls_ill_opt(char c);
void	ls_pathiter(t_option *opt, char *files, char **path);
void	ls_path(t_option *opt, char *files, char *path);
char	*ls_get_files(char *files, char *file, t_option *opt);
char	*ls_get_dirs(char *path, char *dir);
void	ls_insert_dirs(t_dirs *new, t_dirs **dir, unsigned int rev);
char	**ls_sort_files(t_dirs *d, char *files, char *dir_path, t_option *opt);
void	ls_sort(char **files, int start, int end);
void	timesort(char **files, int start, int end, char *dir_path);
void	ls_swap_files(char **s1, char **s2);
time_t	ls_get_time(char *dir_path, char *file);
void	ls_print_data(char **files, char *path, int width, t_option *opt);
void	ls_print_perm(int octal);
void	free_2d(char ***arr_2d);
void	ls_free_lst(t_dirs **head);
void	ls_free_all(char **files, char **dirs, char ***path, t_option **opt);

#endif
