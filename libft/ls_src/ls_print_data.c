/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 13:38:37 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/25 21:57:02 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	total_size(char **files, char *path)
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
		stat(f_path, &buf);
		if (!(buf.st_mode & 040000))
			size += buf.st_blocks;
		ft_strdel(&f_path);
	}
	ft_printf("total %lld\n", size);
}

static void	print_long(char *file, char *path)
{
	struct stat		attr;
	struct passwd	*pwd;
	struct group	*grp;
	char			*f_path;
	char			*date;

	f_path = ft_strjoin(path, "/");
	f_path = ft_strmerge(f_path, ft_strdup(file));
	stat(f_path, &attr);
	ft_strdel(&f_path);
	ls_print_perm(attr.st_mode & 0177777);
	ft_printf("%5d ", attr.st_nlink);
	if ((pwd = getpwuid(attr.st_uid)) != NULL)
		ft_printf("%s ", pwd->pw_name);
	else
		ft_printf("%d ", attr.st_uid);
	if ((grp = getgrgid(attr.st_gid)) != NULL)
		ft_printf(" %s", grp->gr_name);
	else
		ft_printf(" %d", attr.st_gid);
	date = ft_strsub(ctime(&attr.st_mtime), 4, 12);
	ft_printf("%7lld %s ", attr.st_size, date);
	ft_strdel(&date);
}

void	ls_print_data(char **files, char *path, t_option *opt)
{
	int		i;
	int		xfive;

	i = (opt->r > 0) ? opt->r : 0;
	i = (files[i] == NULL) ? 0 : i;
	xfive = i;
	(opt->l) ? total_size(files, path) : NULL;
	while (i >= 0 && files[i])
	{
		while (!opt->a && i >= 0 && files[i] && !ft_memcmp(files[i], ".", 1))
		{
			(opt->r) ? --i : ++i;
			++xfive;
		}
		if (i < 0 || files[i] == NULL)
			break ;
		if (opt->l)
			print_long(files[i], path);
		ft_printf("%-17s", files[i]);
		(opt->r) ? --i : ++i;
		if (opt->l || !((i - xfive) % 5))
			ft_putchar('\n');
	}
	if ((i - xfive) % 5 || opt->R)
		ft_putchar('\n');
}
