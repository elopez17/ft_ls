/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 16:37:19 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/29 21:26:39 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static t_option *get_opt(int argc, char **argv)
{
	t_option	*opt;
	int			i;

	i = 0;
	if (!(opt = (t_option*)malloc(sizeof(t_option))))
		ft_p_exit("malloc");
	ft_bzero(opt, sizeof(t_option));
	if (argc > 1 && argv[1][i] == '-')
		while (argv[1][++i])
		{
			if (argv[1][i] == 'a')
				opt->a = 1;
			else if (argv[1][i] == 't')
				opt->t = 1;
			else if (argv[1][i] == 'r')
				opt->r = 1;
			else if (argv[1][i] == 'l')
				opt->l = 1;
			else if (argv[1][i] == 'R')
				opt->R = 1;
			else if (argv[1][i] == '1')
				opt->one = 1;
		}
	return (opt);
}

static t_dirs	*get_dir(int argc, char **argv, t_option *opt)
{
	t_dirs		*dir;
	int			i;
	struct stat	file;
	char		**file_path;

	if (!(dir = (t_dirs*)malloc(sizeof(t_dirs))))
		ft_p_exit("malloc");
	dir->width = 0;
	if (argc > 1)
	{
		i = (argv[1][0] != '-') ? 1 : 2;
		dir->path = ft_strdup((argv[i] != NULL) ? argv[i] : ".");
		stat(dir->path, &file);
		if ((file.st_mode & 040000) == 0)
		{
			file_path = ls_sort_files(dir, dir->path, ".", opt);
			ls_print_data(file_path, ".", dir->width, opt);
			ls_free_2d(&file_path);
		}
	}
	else
		dir->path = ft_strdup(".");
	dir->files = ft_strdup("");
	dir->next = NULL;
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

int				main(int argc, char **argv)
{
	t_dirs			*dir;
	t_dirs			*head;
	t_option		*opt;
	DIR				*dirp;
	char			**files;

	if (!(opt = get_opt(argc, argv)) || !(dir = get_dir(argc, argv, opt)))
		return (-1);
	head = dir;
	while ((dirp = opendir(dir->path)))
	{
		if (opt->R)
			ft_printf("\n%s:\n", dir->path);
		read_dir(dirp, &dir, opt);
		files = ls_sort_files(dir, dir->files, dir->path, opt);
		ls_print_data(files, dir->path, dir->width, opt);
		ls_free_2d(&files);
		closedir(dirp);
		if (!dir->next || !opt->R)
			break;
		dir = dir->next;
	}
	ls_free_mem(&head, &opt);
	return (0);
}
