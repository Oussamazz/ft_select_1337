/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:53:36 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/10 08:15:29 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	*create_path(const char *s1, const char *s2)
{
	int		strlen_s1;
	char	*s;
	char	*tmp;

	tmp = NULL;
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

char    *get_prev_dir(char *cwd)
{
	char	*last_slash;
	char	*parent;

	last_slash = strrchr(cwd, '/');
	parent = strndup(cwd, last_slash - cwd);
	return (parent);
}

void    browse(int key)
{
    int             counter;
    DIR            *dir;
    struct dirent *folder;
    char    *active;
    char    current;
    char    path;

    active = (*g_HEAD.active_arg)->value;
    current = getcwd(NULL, PATH_MAX);
    if (key == OPEN_KEY)
        path = creat(current, active);
    else
        path = get_prev_dir(current);
    ft_strdel(&current);
    if (!(dir = opendir(path)))
		return (free(path));
    free_all();
    counter = 0;
    while ((folder = readdir(dir)) != NULL)
    {
        if (folder->d_name[0] != '.')
        {
            ft_push_ddl(folder->d_name, counter);
            counter++;
        }
    }
    closedir(dir);
    chdir(path);
    ft_strdel(&path);
}