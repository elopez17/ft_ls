/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 13:38:37 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/18 21:37:19 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	width1 = 1;
static int	width2 = 1;

static void	linkref(char *f_path, char **file)
{
	char buf[256];

	ft_memset(buf, 0, 256);
	readlink(f_path, buf, 256);
	*file = ft_strmer(*file, ft_strjoin(" -> ", buf));
}

static void	total_size(char **files, char *path, t_option *opt)
{
	int			i;
	long long	size;
	struct stat	buf;
	char		*f_path;

	i = -1;
	size = 0;
	while (files[++i])
	{
		f_path = ft_strjoin(path, "/");
		f_path = ft_strmer(f_path, ft_strdup(files[i]));
		lstat(f_path, &buf);
		if (files[i][0] != '.' || opt->a)
		{
			size += buf.st_blocks;
			width1 = MAX(width1, ft_numlen(buf.st_nlink));
			width2 = MAX(width2, ft_numlen(buf.st_size));
		}
		ft_strdel(&f_path);
	}
	if (!opt->files && (ft_strcmp(files[--i], "..") != 0 || opt->a || i != 1))
		ft_printf("total %lld\n", size);
}

static void	print_long(char **file, char *path)
{
	struct stat		attr;
	struct passwd	*pwd;
	struct group	*grp;
	char			*f_path;
	char			*date;

	f_path = ft_strjoin(path, "/");
	f_path = ft_strmerge(f_path, ft_strdup(*file));
	lstat(f_path, &attr);
	IF(((attr.st_mode & S_IFLNK) == S_IFLNK), linkref(f_path, file));
	ft_strdel(&f_path);
	ls_print_perm(attr.st_mode & 0177777);
	ft_printf("%*d ", width1 + 2, attr.st_nlink);
	((pwd = getpwuid(attr.st_uid)) != NULL) ? ft_printf("%s ", pwd->pw_name) :\
			ft_printf("%d ", attr.st_uid);
	((grp = getgrgid(attr.st_gid)) != NULL) ? ft_printf(" %s", grp->gr_name) :\
			ft_printf(" %d", attr.st_gid);
	if (attr.st_mtime >= 253402329600)
	{
		date = ft_strmer(ft_strsub(ctime(&attr.st_mtime), 4, 7),\
				ft_strsub(ctime(&attr.st_mtime), 23, 6));
	}
	else if ((attr.st_mtime - time(NULL)) > 0 || (time(NULL) - attr.st_mtime) > 15768000)
	{
		date = ft_strmer(ft_strsub(ctime(&attr.st_mtime), 4, 7),\
				ft_strsub(ctime(&attr.st_mtime), 19, 5));
	}
	else
		date = ft_strsub(ctime(&attr.st_mtime), 4, 12);
	ft_printf("%*lld %s ", width2 + 2, attr.st_size, date);
	ft_strdel(&date);
}

void	ls_print_data(char **files, char *path, int width, t_option *opt)
{
	int		i;
	int		xfive;

	i = (opt->r > 0) ? opt->r : 0;
	xfive = i;
	(opt->l) ? total_size(files, path, opt) : NULL;
	while (i >= 0 && files[i])
	{
		while (!opt->a && i >= 0 && files[i] && !ft_memcmp(files[i], ".", 1))
		{
			(opt->r) ? --i : ++i;
			(opt->r) ? --xfive : ++xfive;
		}
		if (i < 0 || files[i] == NULL)
			break ;
		(opt->l) ? print_long(&(files[i]), path) : NULL;
		ft_printf("%-*s", (opt->one || opt->l ? 0 : width + 1), files[i]);
		(opt->r) ? --i : ++i;
		if (opt->l || opt->one || !((i - xfive) % 5))
			ft_putchar('\n');
	}
	width1 = 0;
	width2 = 0;
	IF(((i - xfive) % 5 || opt->R) && !opt->one && !opt->l, ft_putchar('\n'));
}
