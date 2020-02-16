/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:53:36 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/16 22:12:43 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	*create_path(const char *s1, const char *s2)
{
	int		strlen_s1;
	char	*s;
	char	*tmp;

	tmp = NULL;
	s = NULL;
	if (s1 && s2)
	{
		s = ft_strdup(s1);
		tmp = s;
		strlen_s1 = ft_strlen(s1);
		if (s1[strlen_s1 - 1] != '/')
		{
			s = ft_strjoin(s1, "/");
			ft_strdel(&tmp);
			tmp = s;
		}
		s = ft_strjoin(s, s2);
		ft_strdel(&tmp);
		return (s);
	}
	return (NULL);
}

static  void    get_items(char *path)
{
	int             counter;
	struct dirent   *dir;
	DIR             *dire;

	dire = NULL;
	dir = NULL;
	if (!(dire = opendir(path)))
		return ;
	counter = 0;
	while ((dir = readdir(dire)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			ft_push_ddl(dir->d_name, counter);
	   		counter++;
		} 
	}
	if (!counter)
		ft_push_ddl("", counter);
	closedir(dire);
	g_HEAD.selected_counter = 0;
}

char    *get_prev_dir(char *cwd)
{
	char	*slash;
	char	*ret;

	if (cwd)
	{
		slash = NULL;
		ret = NULL;
		if (!(slash = strrchr(cwd, '/')))
			return (NULL);
		if (slash - cwd == 0)
			return (ft_strdup("/"));
		ret = ft_strndup(cwd, slash - cwd);
		return (ret);
	}
	return (NULL);
}

void    browse(void)
{
	char            *active;
	char            *current;
	char            *path;

	active = NULL;
	current = NULL;
	path = NULL;
	if (!(active = (*g_HEAD.active_arg)->value))
		return ;
	if (!(current = getcwd(NULL, PATH_MAX)))
		return ;
	path = create_path(current, active);
	ft_strdel(&current);
	if (path == NULL)
		return ;
	if (!check_access(path))
		return (ft_strdel(&path));
	free_all();
	chdir(path);
	get_items(path);
	ft_strdel(&path);
}

void    browse_back(void)
{
	char            *active;
	char            *current;
	char            *path;

	if (!(active = (*g_HEAD.active_arg)->value))
		return ;
	if (!(current = getcwd(NULL, PATH_MAX)))
		return ;
	path = get_prev_dir(current);
	ft_strdel(&current);
	if (path == NULL)
		return ;
	free_all();
	chdir(path);
	get_items(path);
	ft_strdel(&path);
	ft_putstr_fd(DEFAULT_COLOR, g_HEAD.glb_fd);
}
