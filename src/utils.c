/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 22:34:12 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/19 01:06:02 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_type		check_permission(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
		return (UNK_FILE);
	if (S_ISDIR(sb.st_mode))
		return (DIR_FILE);
	else if (sb.st_mode & S_IXUSR)
		return (O_FILE);
	return (UNK_FILE);
}

t_type				get_type(char *data)
{
	char	*name;
	t_type	ret;

	if ((ret = check_permission(data)) != UNK_FILE)
		return (ret);
	name = ft_strrchr(data, '/') ? ft_strrchr(data, '/') + 1 : data;
	if (ft_strlen(name) < 2)
		return (UNK_FILE);
	if (name[0] == '.')
		return (DOT_FILE);
	if (name[ft_strlen(name) - 1] == 'c' && name[ft_strlen(name) - 2] == '.')
		return (C_FILE);
	if (name[ft_strlen(name) - 1] == 'a' && name[ft_strlen(name) - 2] == '.')
		return (A_FILE);
	if ((name[ft_strlen(name) - 1] == 'o' && name[ft_strlen(name) - 2] == '.')
		|| !ft_strcmp(name, "a.out"))
		return (O_FILE);
	if (name[ft_strlen(name) - 1] == 'h' && name[ft_strlen(name) - 2] == '.')
		return (H_FILE);
	if (!ft_strcmp(name, "Makefile"))
		return (MAKE_FILE);
	return (UNK_FILE);
}

static t_direction	direction_(long key)
{
	if (key == UP_KEY)
		return (UP_dir);
	else if (key == DOWN_KEY)
		return (DOWN_dir);
	else if (key == LEFT_KEY)
		return (LEFT_dir);
	else if (key == RIGHT_KEY)
		return (RIGHT_dir);
	return (UNK_dir);
}

static void			continue_(t_direction dir)
{
	t_args *on;

	on = *g_head.active_arg;
	if (dir == LEFT_dir)
		g_head.active_arg = &(on->prev);
	else if (dir == RIGHT_dir)
		g_head.active_arg = &(on->next);
	else if (dir == UP_dir)
		up_();
	else if (dir == DOWN_dir)
		down_();
	else
		ft_putstr_fd("\a", 2);
	return ;
}

void				ft_select_loop(void)
{
	long		key;
	struct stat sb;

	while (true)
	{
		stat((*g_head.active_arg)->value, &sb);
		ft_show();
		key = 0;
		read(0, &key, 6);
		if (key == ENTER_KEY)
			break ;
		else if (key == SPACE_KEY || key == STAR_KEY || key == DLT_ALL_KEY ||
			key == ESC_KEY || key == BSP_KEY)
			ft_select_loop_(key);
		else if (key == OPEN_KEY && S_ISDIR(sb.st_mode) && g_head.real_mode)
			browse();
		else if (key == BACK_KEY && g_head.real_mode)
			browse_back();
		else
			continue_(direction_(key));
	}
}
