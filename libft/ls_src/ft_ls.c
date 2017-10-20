/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 16:37:19 by eLopez            #+#    #+#             */
/*   Updated: 2017/10/19 18:06:06 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		get_opt(t_option **opt, char ***argv)
{
	int	i;

	while (*++*argv != 0 && ***argv == '-')
	{
		if (ft_strcmp(**argv, "--") == 0 && (*argv)++)
			return ;
		i = 0;
		if ((**argv)[1] == '\0')
			break ;
		while ((**argv)[++i])
			if ((**argv)[i] == 'a')
				(*opt)->a = 1;
			else if ((**argv)[i] == 't')
				(*opt)->t = 1;
			else if ((**argv)[i] == 'r')
				(*opt)->r = 1;
			else if ((**argv)[i] == 'l')
				(*opt)->l = 1;
			else if ((**argv)[i] == 'R')
				(*opt)->R = 1;
			else if ((**argv)[i] == '1')
				(*opt)->one = 1;
			else
				ls_ill_opt((**argv)[i]);
	}
}

static t_dirs	*get_dir(t_option *opt, char *files, char *path)
{
	t_dirs		*dir;
	char		**file_path;

	if (!(dir = (t_dirs*)malloc(sizeof(t_dirs))))
		ft_p_exit("malloc");
	dir->width = 0;
	dir->path = ft_strdup(path);
	dir->files = ft_strdup("");
	dir->next = NULL;
	if (*files != '\0')
	{
		file_path = ls_sort_files(dir, files, path, opt);
		ls_print_data(file_path, path, dir->width, opt);
		free_2d(&file_path);
	}
	return (dir);
}

static void		read_dir(DIR *dirp, t_dirs **dir, t_option *opt)
{
	struct dirent	*entry;
	t_dirs			*new;
	t_dirs			*tmp;

	if (!(new = (t_dirs*)ft_memalloc(sizeof(t_dirs))))
		ft_p_exit("malloc");
	tmp = new;
	while ((entry = readdir(dirp)))
	{
		(*dir)->files = ls_get_files((*dir)->files, entry->d_name, opt);
		if (entry->d_type == 4 && ft_memcmp(entry->d_name, ".", 2) && \
ft_memcmp(entry->d_name, "..", 3) && (entry->d_name[0] != '.' || opt->a))
		{
			if (new->path)
			{
				if (!(new->next = (t_dirs*)ft_memalloc(sizeof(t_dirs))))
					ft_p_exit("malloc");
				new = new->next;
			}
			new->path = ls_get_dirs((*dir)->path, entry->d_name);
			new->files = ft_strdup("");
		}
	}
	new->next = NULL;
	(new->path) ? ls_insert_dirs(tmp, dir, opt->r) : ft_memdel((void**)&new);
}

void			ls_path(t_option *opt, char *files, char *path)
{
	t_dirs			*dir;
	t_dirs			*head;
	DIR				*dirp;
	char			**a_file;

	dir = get_dir(opt, files, path);
	head = dir;
	if (*files == '\0')
		while ((dirp = opendir(dir->path)) || errno != 0)
		{
			if (opt->R && dir->path != head->path)
				ft_printf("\n%s:\n", dir->path);
			if (errno == 0)
			{
				read_dir(dirp, &dir, opt);
				a_file = ls_sort_files(dir, dir->files, dir->path, opt);
				ls_print_data(a_file, dir->path, dir->width, opt);
				free_2d(&a_file);
				closedir(dirp);
			}
			else
				ft_printf("ls: %s: %s\n", dir->path, strerror(errno));
			errno = 0;
			if (!dir->next || !opt->R)
				break ;
			dir = dir->next;
		}
	ls_free_lst(&head);
}

int				main(int argc, char **argv)
{
	struct stat	attr;
	t_option	*opt;
	char		*files;
	char		*dirs;
	char		**path;

	argc = 0;
	files = ft_strnew(0);
	dirs = ft_strnew(0);
	if (!(opt = (t_option*)malloc(sizeof(t_option))))
		ft_p_exit("malloc");
	ft_bzero(opt, sizeof(t_option));
	get_opt(&opt, &argv);
	while (*argv++ != 0)
		if (stat(*(argv - 1), &attr) == -1 && lstat(*(argv - 1), &attr) == -1)
		{
			ft_printf("ls: %s: %s\n", *(argv - 1), strerror(errno));
			errno = 0;
			opt->files = 1;
		}
		else if (attr.st_mode & S_IFDIR)
			dirs = ft_strmer(dirs, ft_strjoin(" ", *(argv - 1)));
		else
		{
			files = ft_strmer(files, ft_strjoin(" ", *(argv - 1)));
		}
	path = ft_strsplit(dirs, ' ');
	ls_pathiter(opt, files, path);
	ft_strdel(&files);// free files & dirs & path & opt.
	ft_strdel(&dirs);// free files & dirs & path & opt.
	free_2d(&path);
	ft_memdel((void**)&opt);
	return (0);
}
